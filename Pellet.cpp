#include "Pellet.h"
#include <QPainter>

Pellet::Pellet() {
}

QRectF Pellet::boundingRect() const {
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void Pellet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (collected) return;

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255, 184, 174));
    painter->setPen(Qt::NoPen);
    
    // Small dot in center of tile
    int centerX = TILE_SIZE / 2;
    int centerY = TILE_SIZE / 2;
    painter->drawEllipse(centerX - 3, centerY - 3, 6, 6);
}