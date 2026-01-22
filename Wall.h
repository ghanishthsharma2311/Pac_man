#ifndef WALL_H
#define WALL_H

#include "GameObject.h"

class Wall : public GameObject {
public:
    Wall();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // WALL_H