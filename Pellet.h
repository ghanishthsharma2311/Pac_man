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
};

#endif // PELLET_H