//
// Created by cory on 11/30/23.
//

#ifndef CPPTEST_SIMULATIONOBJECT_H
#define CPPTEST_SIMULATIONOBJECT_H


#include "../math/vec2d.h"

class SimulationObject {
private:
    /* 2-dimensional (x,y) position of the object */
    Vec2D position;
    /* velocity, d(position) / dt */
    Vec2D vel{};
    /* acceleration, d(vel) / dt */
    Vec2D acc{};
public:
    explicit SimulationObject(Vec2D position);

    SimulationObject();

    Vec2D getPosition() const { return position; }
    Vec2D getVelocity() const { return vel; }
    Vec2D getAcceleration() const { return acc; }

    void setAcceleration(Vec2D acceleration);

    /*
     * Work executed every loop update
     * dt: change in time for multiplying to keep position consistency
     */
    void tick(double dt);
};


#endif //CPPTEST_SIMULATIONOBJECT_H
