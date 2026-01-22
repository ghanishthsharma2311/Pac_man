#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "GameObject.h"

/**
 * Base class for collectible items (pellets)
 */
class Collectible : public GameObject {
public:
    Collectible(int p, bool isPower);
    ~Collectible() = default;

    int getPoints() const { return points; }
    bool isPowerPellet() const { return powerPellet; }
    
    bool isCollected() const { return collected; }
    void setCollected(bool c) { collected = c; }

protected:
    bool collected;
    int points;
    bool powerPellet;
};

#endif // COLLECTIBLE_H