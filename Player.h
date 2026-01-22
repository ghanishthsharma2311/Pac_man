#ifndef PLAYER_H
#define PLAYER_H

#include "MovableObject.h"

#define POWER_MODE_DURATION 150 // About 5 seconds at 30 FPS

/**
 * Player (Pac-Man) class
 * Handles keyboard input and power mode
 */
class Player : public MovableObject {
public:
    Player();

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // Power mode
    bool isPowerMode() const { return powerMode; }
    void activatePowerMode();
    void updatePowerMode();
    int getPowerModeTime() const { return powerModeTimer; }

    // Input handling
    void handleKeyPress(int key);

    // Override move to add speed control
    void move(const std::vector<std::vector<int>>& maze);

private:
    int updateCounter = 0; // Control speed
    bool powerMode;
    int powerModeTimer;  // Frames remaining in power mode
    
    // Animation
    int mouthAngle;
    bool mouthOpening;
};

#endif // PLAYER_H