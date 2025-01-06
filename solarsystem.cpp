#include "solarsystem.h"

SolarSystem::SolarSystem(QGraphicsScene *scene, std::vector<_obj> vect, double simulationSpeed){
    scene_t = scene;
    for(size_t i=0;i<vect.size();i++)
    {
        if(vect[i].name == "sun"){
            sun = new Planet(1.989e30, vect[i].x.toInt() * 1e9,vect[i].y.toInt() * 1e9, 0, 0);
            sun->setBrush(Qt::yellow);
            sun->setPos(vect[i].x.toInt(),vect[i].y.toInt());
            sun->setRect(-20, -20, 40, 40);
            vectorSun.push_back(sun);
            scene->addItem(sun);
        }
        else if(vect[i].name == "planet")
        {
            planet = new Planet(5.972e24, vect[i].x.toInt() * 1e9, 0, 0, 29780);
            planet->setBrush(Qt::blue);
            planet->setPos(vect[i].x.toInt(),vect[i].y.toInt());
            vectorPlanet.push_back(planet);
            scene->addItem(planet);
        }
    }
    if (!vectorSun.empty() && !vectorPlanet.empty())
    {
        timer = new QTimer(this);
        if (timer == nullptr) {
            qDebug() << "Timer is null!";
        }
        if (!connect(timer, &QTimer::timeout, this, &SolarSystem::update)) {
            qDebug() << "Failed to connect timer signal to update slot!";
        }
        timer->start(simulationSpeed);
    }
}
void SolarSystem::update() {
    for (size_t i = 0; i < vectorPlanet.size(); i++) {
        double totalAx = 0.0;
        double totalAy = 0.0;
        //qDebug()<<"++";
        //qDebug()<<vectorPlanet[i]->x<<" "<<vectorPlanet[i]->y;
        for (size_t j = 0; j < vectorSun.size(); j++) {
            //qDebug()<<vectorSun[j]->x<<" "<<vectorSun[j]->y;
            double dx = vectorSun[j]->x - vectorPlanet[i]->x;
            double dy = vectorSun[j]->y - vectorPlanet[i]->y;
            double r = sqrt(dx * dx + dy * dy);
            //qDebug()<<r;
            if (r <= 2e+10) {
                scene_t->removeItem(vectorPlanet[i]);
                vectorPlanet.erase(vectorPlanet.begin() + i);
                break;
            }

            double F = G * vectorSun[j]->mass * vectorPlanet[i]->mass / (r * r);
            double ax = F * dx / r / vectorPlanet[i]->mass;
            double ay = F * dy / r / vectorPlanet[i]->mass;

            totalAx += ax;
            totalAy += ay;
        }

        vectorPlanet[i]->vx += totalAx * 3600;
        vectorPlanet[i]->vy += totalAy * 3600;

        vectorPlanet[i]->updatePosition(3600);
        //qDebug()<<"++";
    }
}
void SolarSystem::updateSimulationSpeed(double newSpeed) {
    if (newSpeed > 0) {
        simulationSpeed = newSpeed;
        if (timer != nullptr) {
            timer->stop();
            timer->start(simulationSpeed);
        }
    }
}


