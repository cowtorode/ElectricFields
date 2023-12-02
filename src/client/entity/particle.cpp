//
// Created by cory on 11/30/23.
//

#include "particle.h"

Particle::Particle(Vec2D position, double mass, int charge) : SimulationObject(position), mass(mass), charge(charge) { }

Particle::Particle(double mass, int charge) : Particle({0, 0}, mass, charge) { }
