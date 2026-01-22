#include "Enemy.h"

Enemy::Enemy() : frightened(false), spawnX(0), spawnY(0) {
}

void Enemy::updateBehavior(const QPointF& playerPos) {
    (void)playerPos;
}

void Enemy::respawn() {
}