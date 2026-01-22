#ifndef ENEMY_H
#define ENEMY_H

#include "MovableObject.h"

class Enemy : public MovableObject {
public:
    Enemy();
    ~Enemy() = default;

    void updateBehavior(const QPointF& playerPos);

    bool isFrightened() const { return frightened; }
    void setFrightened(bool scared) { frightened = scared; }

    // Respawn handling
    void respawn();
    
    int getSpawnX() const { return spawnX; }
    int getSpawnY() const { return spawnY; }

protected:
    bool frightened;
    int spawnX;
    int spawnY;
};

#endif // ENEMY_H