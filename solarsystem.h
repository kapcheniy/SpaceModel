#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H
#include <QApplication>
#include "planet.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <cmath>
#include <vector>
#include "_obj.h"
#include <windows.h>

const double G = 6.67430e-11;
class SolarSystem : public QObject {
    Q_OBJECT
private:
    std::vector<Planet*> vectorPlanet;
    std::vector<Planet*> vectorSun;
    QGraphicsScene *scene_t;
    double simulationSpeed;
public:
    Planet *sun;
    Planet *planet;
    QTimer *timer;
    SolarSystem(QGraphicsScene *scene, std::vector<_obj> vect, double simulationSpeed);
    void updateSimulationSpeed(double newSpeed);
public slots:
    void update();
};

#endif // SOLARSYSTEM_H
