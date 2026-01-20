#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "GameObject.h"

/**
 * Base class for collectible items (pellets)
 */
class Collectible : public GameObject {
public:
    Collectible();
    virtual ~Collectible() = default;

    virtual int getPoints() const = 0;
    virtual bool isPowerPellet() const = 0;
    
    bool isCollected() const { return collected; }
    void setCollected(bool c) { collected = c; }

protected:
    bool collected;
};

#endif // COLLECTIBLE_H