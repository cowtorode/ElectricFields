//
// Created by cory on 11/30/23.
//

#include "simulationobject.h"

SimulationObject::SimulationObject(Vec2D position) : position(position) { }

SimulationObject::SimulationObject() : SimulationObject({0, 0}) { }

void SimulationObject::tick(double dt) {
    vel += acc * dt; // change velocity (speed) according to acceleration and delta time
    // reset acceleration. The rules are, only accelerate if told before tick,
    // and speed stays the same between frames. It'd be pretty weird if an object
    // suddenly stopped just because we didn't give it its speed, that violates
    // newtons first law of motion which states that velocity is constant unless
    // accelerated...
    acc = {0, 0};
    position += vel; // change position according to velocity
}

void SimulationObject::setAcceleration(Vec2D acceleration) {
    acc = acceleration;
}
