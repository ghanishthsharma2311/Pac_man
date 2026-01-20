#include "Wall.h"
#include <QPainter>

Wall::Wall() {
}

QRectF Wall::boundingRect() const {
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(QColor(33, 33, 222));
    painter->setPen(QPen(QColor(66, 66, 255), 1));
    painter->drawRect(0, 0, TILE_SIZE - 1, TILE_SIZE - 1);
}