#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "GameObject.h"
#include <vector>

/**
 * Base class for objects that can move
 * Handles direction and grid-based movement
 */
class MovableObject : public GameObject {
public:
    enum Direction {
        NONE = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    MovableObject();
    virtual ~MovableObject() = default;

    // Movement
    virtual void move(const std::vector<std::vector<int>>& maze);
    
    Direction getDirection() const { return currentDirection; }
    void setDirection(Direction dir) { nextDirection = dir; }

protected:
    Direction currentDirection;
    Direction nextDirection;

    // Smooth movement state
    static constexpr int MOVEMENT_SPEED = 5; // Pixels per frame (must be divisor of TILE_SIZE=30)
    int pixelMoved = 0; // How many pixels moved into current tile transition

    // Check if move to position is valid
    bool isValidMove(int x, int y, const std::vector<std::vector<int>>& maze) const;
    
    // Try to change direction
    bool tryChangeDirection(const std::vector<std::vector<int>>& maze);
};

#endif // MOVABLEOBJECT_H