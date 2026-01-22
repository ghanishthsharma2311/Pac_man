#include "GameObject.h"

GameObject::GameObject() { gridX=0; gridY=0; 
}

void GameObject::setGridPosition(int x, int y) {
    gridX = x;
    gridY = y;
    setPos(gridToScene(x, y));
}

QPointF GameObject::gridToScene(int x, int y) const {
    return QPointF(x * TILE_SIZE, y * TILE_SIZE);
}