#ifndef GHOST_H
#define GHOST_H

#include "Enemy.h"
#include <QColor>
#include <vector>

class Ghost : public Enemy {
public:
    Ghost(const QColor& color, int spawnX, int spawnY);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    
    void updateBehavior(const QPointF& playerPos);
    
    // Respawn at starting position
    void respawn();

    // Movement with maze reference
    void moveGhost(const std::vector<std::vector<int>>& maze);

private:
    QColor color;
    int updateCounter; // Slows down ghost movement
    
    
    Direction chooseChaseDirection(const QPointF& target, const std::vector<std::vector<int>>& maze);
    
    
      //Frightened :Moves randomly away from player
    Direction chooseScaredDirection(const QPointF& playerPos, const std::vector<std::vector<int>>& maze);
    
    // Calculate Manhattan distance
    int manhattanDistance(int x1, int y1, int x2, int y2) const;
};

#endif 