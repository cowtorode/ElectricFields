//
// Created by cory on 11/30/23.
//

#ifndef CPPTEST_PARTICLE_H
#define CPPTEST_PARTICLE_H

#include "simulationobject.h"
#include "../math/constants.h"

class Particle : public SimulationObject {
private:
    int charge;
    double mass;
public:
    Particle(Vec2D position, double mass, int charge);

    Particle(double mass, int charge);

    int getElectricalCharge() const { return charge; }

    double getMass() const { return mass; }
};


#endif //CPPTEST_PARTICLE_H
