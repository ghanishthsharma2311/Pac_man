#ifndef PELLET_H
#define PELLET_H

#include "Collectible.h"

/**
 * Regular pellet (small dots)
 * Worth 10 points
 */
class Pellet : public Collectible {
public:
    Pellet();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getPoints() const override { return 10; }
    bool isPowerPellet() const override { return false; }
};

#endif // PELLET_H