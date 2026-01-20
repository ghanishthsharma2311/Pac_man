#ifndef ENEMY_H
#define ENEMY_H

#include "MovableObject.h"

/**
 * Abstract base class for enemies
 * Defines interface for AI behavior
 */
class Enemy : public MovableObject {
public:
    Enemy();
    virtual ~Enemy() = default;

    // AI behavior - must be implemented by subclasses
    virtual void updateBehavior(const QPointF& playerPos) = 0;

    // Frightened mode (activated by power pellet)
    bool isFrightened() const { return frightened; }
    void setFrightened(bool scared) { frightened = scared; }

    // Respawn handling
    virtual void respawn() = 0;
    
    int getSpawnX() const { return spawnX; }
    int getSpawnY() const { return spawnY; }

protected:
    bool frightened;
    int spawnX;
    int spawnY;
};

#endif // ENEMY_H