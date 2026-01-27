#include "Player.h"
#include <Qt>
#include <cmath>

Player::Player() 
    : powerMode(false), powerModeTimer(0), mouthAngle(45), mouthOpening(false) {
    canEnterGhostHouse = false;
}

QRectF Player::boundingRect() const {
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw Pac-Man as a circle with a mouth
    painter->setRenderHint(QPainter::Antialiasing);
    
    // Color based on power mode
    QColor color;
    if (powerMode) {
        color = QColor(255, 255, 0);
    } else {
        color = QColor(255, 220, 0);
    }

    painter->setBrush(color);
    painter->setPen(Qt::NoPen);

    // Determine mouth direction based on movement
    int startAngle = 0;
    switch (currentDirection) {
        case RIGHT: startAngle = 0; break;
        case DOWN:  startAngle = 270; break;
        case LEFT:  startAngle = 180; break;
        case UP:    startAngle = 90; break;
        default:    startAngle = 0; break;
    }

    // Draw pie (circle with mouth cutout)
    int spanAngle = 360 - (mouthAngle * 2);
    painter->drawPie(2, 2, TILE_SIZE - 4, TILE_SIZE - 4, 
                     (startAngle + mouthAngle) * 16, spanAngle * 16);

    // Animate mouth
    if (currentDirection != NONE) {
        if (mouthOpening) {
            mouthAngle += 3;
            if (mouthAngle >= 45) mouthOpening = false;
        } else {
            mouthAngle -= 3;
            if (mouthAngle <= 5) mouthOpening = true;
        }
    }
}

void Player::activatePowerMode() {
    powerMode = true;
    powerModeTimer = POWER_MODE_DURATION;
}

void Player::updatePowerMode() {
    if (powerMode) {
        powerModeTimer--;
        if (powerModeTimer <= 0) {
            powerMode = false;
            powerModeTimer = 0;
        }
    }
}

void Player::handleKeyPress(int key) {
    switch (key) {
        case Qt::Key_Up:
            setDirection(UP);
            break;
        case Qt::Key_Down:
            setDirection(DOWN);
            break;
        case Qt::Key_Left:
            setDirection(LEFT);
            break;
        case Qt::Key_Right:
            setDirection(RIGHT);
            break;
    }
}

void Player::move(const std::vector<std::vector<int>>& maze) {
    // Rely on MovableObject::move for smooth movement
    MovableObject::move(maze);
    
    // We can also try change direction mid-tile if we want, but Base behavior is safer for now
    if (pixelMoved == 0) {
        tryChangeDirection(maze);
    }
}