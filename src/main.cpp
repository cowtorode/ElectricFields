//
// File: main.cpp
// Author: Cory Torode
// Description: Main class for project quick simulates electric fields
// Date: November 30, 2023
//

#include <iostream>
#include <GLFW/glfw3.h>
#include "client/simulation.h"

#define DEBUG true

/*
 * Initialize all external libraries
 */
void init() {
    std::cout << "Initializing external libraries..." << std::endl;
    /* Initialize glfw */
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }
}

/*
 * Execute main program functions
 */
void run() {
    std::cout << "Welcome to the 2D Electric Field Simulator!" << std::endl;
    std::cout << " * Author: Cory Torode" << std::endl;
    std::cout << " * Date: November 30, 2023" << std::endl;
    std::cout << "Beginning electric field simulation..." << std::endl;
    std::cout << " * Debug Mode: " << DEBUG << std::endl;

    init(); // init external libraries such as glfw
    Simulation simulation{};

    std::cout << "Adding simulation particles..." << std::endl;

    simulation.addParticle(new Particle({1, 0.1}, 0.001, 50));
    simulation.addParticle(new Particle({-1, 0}, 0.1, -50));
    simulation.addParticle(new Particle({0.1, 1}, 0.01, 50));
    simulation.addParticle(new Particle({3, -6}, 100, -100));

    std::cout << "Initializing glfw window..." << std::endl;
    simulation.init(1280, 720, "Interactions Between Charged Particles");
    std::cout << "Starting electric field model..." << std::endl;
    std::cout << "Controls" << std::endl;
    std::cout << " ESC  * Exit simulation" << std::endl;
    std::cout << " UP   * Increase simulation speed by 10%" << std::endl;
    std::cout << " DOWN * Decrease simulation speed by 10%" << std::endl;
    simulation.start(); // open window and start simulation
}

int main() {
    run();
    return 0;
}
