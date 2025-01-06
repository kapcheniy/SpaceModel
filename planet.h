#ifndef PLANET_H
#define PLANET_H
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
const double SCALE = 1e-9;

class Planet : public QGraphicsEllipseItem {
public:
    double mass;
    double x, y;
    double vx, vy;
    Planet(double mass, double x, double y, double vx, double vy, QGraphicsEllipseItem *parent = nullptr)
        : QGraphicsEllipseItem(parent), mass(mass), x(x), y(y), vx(vx), vy(vy) {
        setRect(-5, -5, 10, 10);
        setFlag(QGraphicsItem::ItemIsMovable);
    }
    // Planet(qreal x, qreal y, qreal width, qreal height)
    //     : QGraphicsEllipseItem(x, y, width, height) {
    //     setBrush(Qt::blue);  // Задаем цвет планеты
    //     setFlag(QGraphicsItem::ItemIsMovable);  // Разрешаем перемещать планету
    // }
    void updatePosition(double dt);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PLANET_H
