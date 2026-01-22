#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

#define TILE_SIZE 30

class GameObject : public QGraphicsItem {
public:
    GameObject();
    ~GameObject() = default;

    // Grid position (in tiles)  updates the logic coordinates (gridX/Y) and immediately tells the Qt engine to move the visual object
    int getGridX() const { return gridX; }    
    int getGridY() const { return gridY; }
    void setGridPosition(int x, int y);

protected:
    int gridX;
    int gridY;

    // Convert grid coordinates to scene coordinates
    QPointF gridToScene(int x, int y) const;
};

#endif 