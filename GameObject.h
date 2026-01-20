#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPointF>

/**
 * Base class for all game objects
 * Provides basic position and collision handling
 */
class GameObject : public QGraphicsItem {
public:
    GameObject();
    virtual ~GameObject() = default;

    // Grid position (in tiles)
    int getGridX() const { return gridX; }
    int getGridY() const { return gridY; }
    void setGridPosition(int x, int y);

    // Tile size constant
    static constexpr int TILE_SIZE = 30;

protected:
    int gridX;
    int gridY;

    // Convert grid coordinates to scene coordinates
    QPointF gridToScene(int x, int y) const;
};

#endif // GAMEOBJECT_H