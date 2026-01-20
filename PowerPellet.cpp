#include "PowerPellet.h"
#include <QPainter>

PowerPellet::PowerPellet() : animationFrame(0), growing(true) {
}

QRectF PowerPellet::boundingRect() const {
    return QRectF(0, 0, TILE_SIZE, TILE_SIZE);
}

void PowerPellet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if (collected) return;

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QColor(255, 184, 174));
    painter->setPen(Qt::NoPen);
    
    // Larger pulsing dot
    int centerX = TILE_SIZE / 2;
    int centerY = TILE_SIZE / 2;
    int radius = 8 + (animationFrame / 5); // Pulse between 8-10 pixels
    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
}

void PowerPellet::animate() {
    if (growing) {
        animationFrame++;
        if (animationFrame >= 10) growing = false;
    } else {
        animationFrame--;
        if (animationFrame <= 0) growing = true;
    }
}