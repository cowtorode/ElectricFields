//
// Created by cory on 10/22/23.
//

#ifndef CPPTEST_SIMULATION_H
#define CPPTEST_SIMULATION_H


#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include "entity/particle.h"

class Simulation {
    float width;
    float height;
    bool paused = false;
private:
    // FIELDS
    GLFWwindow *window = nullptr;

    std::vector<Particle *> particles;

    // METHODS
    void handleInput();

    void update();

    void render();

    void loop();

public:
    Simulation();

    ~Simulation();

    void printParticles();

    void init(int x, int y, const char *title);

    void start();

    void addParticle(Particle *particle);
};


#endif //CPPTEST_SIMULATION_H
