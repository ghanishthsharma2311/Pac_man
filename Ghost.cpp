#include "Ghost.h"
#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include <random>
#include <QGraphicsScene>
#include <QGraphicsItem>

Ghost::Ghost(const QColor& col, int sx, int sy) 
    : color(col), updateCounter(0) {
    spawnX = sx;
    spawnY = sy;
    setGridPosition(sx, sy);
    currentDirection = RIGHT; // Start moving right
    canEnterGhostHouse = true;
}

QRectF Ghost::boundingRect() const {
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing);
    
    // Change color when frightened
    QColor drawColor = frightened ? QColor(0, 0, 255) : color;
    painter->setBrush(drawColor);
    painter->setPen(Qt::NoPen);

    // Draw ghost body (rounded top, wavy bottom)
    QPainterPath path;
    path.moveTo(2, TILE_SIZE);
    
    // Bottom wave pattern
    path.lineTo(2, TILE_SIZE);
    path.lineTo(6, TILE_SIZE - 4);
    path.lineTo(10, TILE_SIZE);
    path.lineTo(14, TILE_SIZE - 4);
    path.lineTo(18, TILE_SIZE);
    path.lineTo(22, TILE_SIZE - 4);
    path.lineTo(26, TILE_SIZE);
    path.lineTo(TILE_SIZE - 2, TILE_SIZE);
    
    // Right side
    path.lineTo(TILE_SIZE - 2, TILE_SIZE / 2);
    
    // Top arc
    path.arcTo(2, 2, TILE_SIZE - 4, TILE_SIZE - 4, 0, 180);
    
    path.closeSubpath();
    painter->drawPath(path);

    // Draw eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(8, 8, 6, 8);
    painter->drawEllipse(16, 8, 6, 8);
    
    // Eye pupils
    if (!frightened) {
        painter->setBrush(Qt::black);
        int pupilOffsetX = 0, pupilOffsetY = 0;
        
        switch (currentDirection) {
            case UP:    pupilOffsetY = -2; break;
            case DOWN:  pupilOffsetY = 2; break;
            case LEFT:  pupilOffsetX = -2; break;
            case RIGHT: pupilOffsetX = 2; break;
            default: break;
        }
        
        painter->drawEllipse(10 + pupilOffsetX, 10 + pupilOffsetY, 3, 3);
        painter->drawEllipse(18 + pupilOffsetX, 10 + pupilOffsetY, 3, 3);
    }
}

void Ghost::respawn() {
    setGridPosition(spawnX, spawnY);
    currentDirection = RIGHT;
    nextDirection = NONE;
    frightened = false;
    pixelMoved = 0; // Reset smooth movement offset
}

int Ghost::manhattanDistance(int x1, int y1, int x2, int y2) const {
    return std::abs(x1 - x2) + std::abs(y1 - y2);
}

MovableObject::Direction Ghost::chooseChaseDirection(const QPointF& target, const std::vector<std::vector<int>>& maze) {
    int targetX = static_cast<int>(target.x() / TILE_SIZE);
    int targetY = static_cast<int>(target.y() / TILE_SIZE);
    
    // Evaluate all four directions
    Direction directions[] = {UP, DOWN, LEFT, RIGHT};
    Direction bestDirection = currentDirection;
    int bestDistance = 9999;
    
    for (Direction dir : directions) {
        // Don't reverse direction (unless stuck)
        if ((dir == UP && currentDirection == DOWN) ||
            (dir == DOWN && currentDirection == UP) ||
            (dir == LEFT && currentDirection == RIGHT) ||
            (dir == RIGHT && currentDirection == LEFT)) {
            continue;
        }
        
        int testX = gridX;
        int testY = gridY;
        
        switch (dir) {
            case UP:    testY--; break;
            case DOWN:  testY++; break;
            case LEFT:  testX--; break;
            case RIGHT: testX++; break;
            default: break;
        }
        
        if (isValidMove(testX, testY, maze)) {
            int dist = manhattanDistance(testX, testY, targetX, targetY);
            if (dist < bestDistance) {
                bestDistance = dist;
                bestDirection = dir;
            }
        }
    }
    
    return bestDirection;
}

MovableObject::Direction Ghost::chooseScaredDirection(const QPointF& playerPos, const std::vector<std::vector<int>>& maze) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    int playerX = static_cast<int>(playerPos.x() / TILE_SIZE);
    int playerY = static_cast<int>(playerPos.y() / TILE_SIZE);
    
    // Collect valid directions that move away from player
    std::vector<Direction> validDirs;
    Direction directions[] = {UP, DOWN, LEFT, RIGHT};
    
    for (Direction dir : directions) {
        int testX = gridX;
        int testY = gridY;
        
        switch (dir) {
            case UP:    testY--; break;
            case DOWN:  testY++; break;
            case LEFT:  testX--; break;
            case RIGHT: testX++; break;
            default: break;
        }
        
        if (isValidMove(testX, testY, maze)) {
            int newDist = manhattanDistance(testX, testY, playerX, playerY);
            int currentDist = manhattanDistance(gridX, gridY, playerX, playerY);
            
            // Prefer directions that increase distance from player
            if (newDist >= currentDist) {
                validDirs.push_back(dir);
            }
        }
    }
    
    // If no good directions, take any valid direction
    if (validDirs.empty()) {
        for (Direction dir : directions) {
            int testX = gridX;
            int testY = gridY;
            
            switch (dir) {
                case UP:    testY--; break;
                case DOWN:  testY++; break;
                case LEFT:  testX--; break;
                case RIGHT: testX++; break;
                default: break;
            }
            
            if (isValidMove(testX, testY, maze)) {
                validDirs.push_back(dir);
            }
        }
    }
    
    // Pick random valid direction
    if (!validDirs.empty()) {
        std::uniform_int_distribution<> dis(0, validDirs.size() - 1);
        return validDirs[dis(gen)];
    }
    
    return currentDirection;
}

void Ghost::updateBehavior(const QPointF& playerPos) {
   
    // Actual movement happens in moveGhost()
    Q_UNUSED(playerPos);
}

void Ghost::moveGhost(const std::vector<std::vector<int>>& maze) {
    // Ghosts move same speed as player now (or we can use updateCounter to skip SOME frames if we want them slower)
    // For smooth movement, we should probably keep them moving every frame but maybe slower speed constant?
    // Since MOVEMENT_SPEED is static const, we can't change it per instance easily without more refactor.
    // So let's throttle ghosts by skipping every OTHER frame to make them half speed of player?
    // Or just run every frame. If player is too fast, we can adjust SPEED.
    
    // Let's make ghosts slightly slower than Player (skip every 3rd frame?)
    updateCounter++;
    if (updateCounter % 3 == 0) return; // 2/3 speed of player
    
    // Get player position from scene
    QPointF playerPos(0, 0);
    if (scene()) {
        auto items = scene()->items();
        for (auto item : items) {
            if (item != this && dynamic_cast<Ghost*>(item) == nullptr) {
                playerPos = item->pos();
                break;
            }
        }
    }
    
    // Choose direction based on mode
    Direction newDir;
    if (frightened) {
        newDir = chooseScaredDirection(playerPos, maze);
    } else {
        newDir = chooseChaseDirection(playerPos, maze);
    }
    
    setDirection(newDir);
    MovableObject::move(maze);
}