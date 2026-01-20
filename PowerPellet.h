#ifndef POWERPELLET_H
#define POWERPELLET_H

#include "Collectible.h"

/**
 * Power pellet (large dots)
 * Worth 50 points and activates power mode
 */
class PowerPellet : public Collectible {
public:
    PowerPellet();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    int getPoints() const override { return 50; }
    bool isPowerPellet() const override { return true; }

    void animate();

private:
    int animationFrame;
    bool growing;
};

#endif // POWERPELLET_H