#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "GameObject.h"
#include <vector>

#define MOVEMENT_SPEED 5

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
    ~MovableObject() = default;

    // Movement
    void move(const std::vector<std::vector<int>>& maze);
    
    Direction getDirection() const { return currentDirection; }  //to see where the object is currently going
    void setDirection(Direction dir) { nextDirection = dir; }   //to set the next direction of the object

protected:
    Direction currentDirection;
    Direction nextDirection;

    // Smooth movement state
    int pixelMoved = 0; // How many pixels moved into current tile transition

    // Check if move to position is valid
    bool isValidMove(int x, int y, const std::vector<std::vector<int>>& maze) const;
    
    // Try to change direction
    bool tryChangeDirection(const std::vector<std::vector<int>>& maze);
};

#endif