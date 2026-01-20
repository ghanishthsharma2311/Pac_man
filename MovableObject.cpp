#include "MovableObject.h"

MovableObject::MovableObject() 
    : currentDirection(NONE), nextDirection(NONE), pixelMoved(0) {
}

bool MovableObject::isValidMove(int x, int y, const std::vector<std::vector<int>>& maze) const {
    // Check bounds
    if (y < 0 || y >= static_cast<int>(maze.size())) return false;
    if (x < 0 || x >= static_cast<int>(maze[0].size())) return false;
    
    // Check if tile is walkable (0 = empty, 1 = wall)
    return maze[y][x] != 1;
}

bool MovableObject::tryChangeDirection(const std::vector<std::vector<int>>& maze) {
    if (nextDirection == NONE || nextDirection == currentDirection) {
        return false;
    }

    int newX = gridX;
    int newY = gridY;

    switch (nextDirection) {
        case UP:    newY--; break;
        case DOWN:  newY++; break;
        case LEFT:  newX--; break;
        case RIGHT: newX++; break;
        default: break;
    }

    if (isValidMove(newX, newY, maze)) {
        currentDirection = nextDirection;
        return true;
    }

    return false;
}

void MovableObject::move(const std::vector<std::vector<int>>& maze) {
    // If not currently moving between tiles, try to change direction
    if (pixelMoved == 0) {
        tryChangeDirection(maze);
    }

    if (currentDirection == NONE) return;

    // Move 'MOVEMENT_SPEED' pixels
    int speed = MOVEMENT_SPEED;
    
    // Calculate new position in grid terms
    int dx = 0;
    int dy = 0;
    
    switch (currentDirection) {
        case UP:    dy = -1; break;
        case DOWN:  dy = 1; break;
        case LEFT:  dx = -1; break;
        case RIGHT: dx = 1; break;
        default: break;
    }
    
    // Check if we can proceed into the next tile
    // We only check this at the beginning of a tile movement
    if (pixelMoved == 0) {
        if (!isValidMove(gridX + dx, gridY + dy, maze)) {
            // Hit a wall
            currentDirection = NONE;
            return;
        }
    }
    
    // Update visual position
    QPointF currentPos = pos();
    setPos(currentPos.x() + (dx * speed), currentPos.y() + (dy * speed));
    pixelMoved += speed;
    
    // Check if we completed a full tile move
    if (pixelMoved >= TILE_SIZE) {
        // Snap to grid
        gridX += dx;
        gridY += dy;
        setGridPosition(gridX, gridY); // Resets pos to exact grid coordinates to prevent drift
        pixelMoved = 0;
        
        // Try to change direction immediately after finishing a move
        if (nextDirection != NONE && nextDirection != currentDirection) {
            tryChangeDirection(maze);
        }
    }
}