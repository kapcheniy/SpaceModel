#include "planet.h"
void Planet::updatePosition(double dt){
    x += vx * dt;
    y += vy * dt;
    setPos(x * SCALE, y * SCALE);
}
void Planet::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsEllipseItem::mousePressEvent(event);
}

void Planet::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
    QPointF mousePos = event->scenePos();

    x = mousePos.x() * 10e8;
    y = mousePos.y() * 10e8;
    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void Planet::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {

    QGraphicsEllipseItem::mouseReleaseEvent(event);
}
