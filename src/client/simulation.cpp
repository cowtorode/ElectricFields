//
// Created by cory on 10/22/23.
//

#include <iostream>
#include <stdexcept>
#include <cmath>
#include "simulation.h"
#include "math/constants.h"

Simulation::Simulation()  = default;

Simulation::~Simulation() {
    for (Particle *particle: particles) {
        delete particle;
    }
}

void Simulation::init(int x, int y, const char* title) {
    this->width  = float(x);
    this->height = float(y);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(x, y, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Unable to create glfw window");
    }

    GLFWmonitor *monitor    = glfwGetPrimaryMonitor();
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    // todo: more robust initialization options possibly for future projects
    // center
    glfwSetWindowPos(window, (mode->width - x) / 2, (mode->height - y) / 2);
}

void Simulation::start() {
    if (window == nullptr) {
        init(512, 512, "Hello World!");
    }
    loop();
}

void Simulation::printParticles() {
    for (Particle *p : particles) {
        std::cout << "(" << p->getPosition().getX() << ", " << p->getPosition().getY() << ")" << std::endl;
    }
}

void Simulation::loop() {
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Set background clear color
    glClearColor(0.2f, 0.4f, 0.6f, 1.0f);

    static double limitFPS = 1.0 / 60.0; // 60 fps, 1 / 60 seconds per frame... rate of update

    double lastTime  = glfwGetTime();
    double timer     = lastTime;
    double deltaTime = 0;
    double nowTime;
    int frames       = 0;
    int updates      = 0;

    // See https://stackoverflow.com/questions/20390028/c-using-glfwgettime-for-a-fixed-time-step
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        handleInput();

        // - Measure time
        nowTime    = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime   = nowTime;

        // - Only update at 60 frames / s
        while (deltaTime >= 1.0) {
            update();   // - Update function
            updates++;
            deltaTime--;
        }
        // - Render at maximum possible frames
        render(); // - Render function

        frames++;

        // - Reset after one second
        if (glfwGetTime() - timer > 1.0) {
            timer++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
            // printParticles();
        }

        /* Poll for and process events */
        // Note: this blocks
        glfwPollEvents();
    }

    glfwTerminate();
}

double speed = 1;
bool spaceHeld = false;

void Simulation::handleInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        speed *= 1.1;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        speed /= 1.1;
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!spaceHeld) {
            spaceHeld = true;
            paused = !paused;
        }
    } else {
        spaceHeld = false;
    }
}

void Simulation::update() {
    /* acc being applied to iParticle particle iteration of i */
    Vec2D acc{0, 0}; // F = ma, a = F / m, F == Energy of electric field
    Particle *iParticle;
    Particle *jParticle;

    Vec2D diff; // i - j
    double dist; // |i - j|

    // p0, p1, p2, ... pn...
    // for (/* iterate through each particle */) {
    //     // get i particle
    //     for (/* iterate through each particle */)
    //     // get j particle
    //     // if i particle is not j, we calculate how much j is accelerating i

    // FORCE == MASS * ACC
    /* (force here is really magnitude per charge since electric
       fields don't accelerate non-charged particles) */
    // FORCE (on i particle) == SUM OF (all j particle) ELECTRIC FIELD MAGNITUDES (at i) (Ei)
    // FORCE == Ei
    // Ei  == MASS * ACC
    // ACC == Ei / MASS

    // CONSTANTS
    // k == coulomb's constant
    // C == elementary charge

    // VARIABLES or DEFINITIONS
    // Let qj be the electrical charge of the current particle j in iteration.
    // Let i, j be the positions of the current particles i, j in iteration respectively.
    // Let mi be the mass of the current particle i in iteration.
    // Let ai be the acceleration on the current particle i in iteration from all other particle j's.
    // Let Ej be the force per charge that the current particle j in iteration -
    //   is exerting on the current particle i in iteration.
    // Let Ei be the force per charge among all other particle j's on the current particle i in iteration.
    // Let r be the distance between i, j.

    // r  = |i - j|
    // Ej = [(i - j) / r] * k * C * (-qi * qj) / (r * r)
    // Ei = (Σ Ej)
    // ai = Ei / mi


    if (!paused) {
        // iterate through each particle, checking every other particle's influence and
        // calculating new position. Repeat until all particle accelerations have been calculated
        for (int i = 0; i < particles.size(); i++) {
            iParticle = particles[i];
            for (int j = 0; j < particles.size(); j++) {
                if (i != j) { // particle i doesn't influence itself
                    jParticle = particles[j];
                    diff = iParticle->getPosition() - jParticle->getPosition();
                    dist = diff.getMagnitude();

                    acc += diff * jParticle->getElectricalCharge() / (dist * dist * dist);
                }
                // a charged particles isn't influenced by its own electric field,
                // but the acc magnitude of the sum of all other particles in the universe
            }
            iParticle->setAcceleration(acc * ELEMENTARY_CHARGE * COULOMB_CONSTANT * iParticle->getElectricalCharge() /
                                       iParticle->getMass());
            acc = {0, 0};
        }
        // tick only after every particle's acceleration has been calculated so that
        // next frame positions aren't incorporated into current acceleration calculations
        for (auto &particle: particles) {
            particle->tick(speed);
        }
    }
}

void drawFilledCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * std::cos(theta);
        float y = r * std::sin(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void Simulation::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = width / height;
    glOrtho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);

    Vec2D position;
    for (Particle* particle : particles) {
        position = particle->getPosition();
        int q = particle->getElectricalCharge();

        if (-256 < q && q <= 0) { // [-255, 0]
            glColor3ub(255 + q, 255 + q, 255);
        } else if (0 < q && q <= 255) { // [1, 255]
            glColor3ub(255, 255 - q, 255 - q);
        }
        drawFilledCircle(float(position.getX() * 0.1), float(position.getY() * 0.1), 0.01f, 12);
    }
    /* Stop rendering */

    /* Swap front and back buffers */
    glfwSwapBuffers(window);
}

void Simulation::addParticle(Particle *particle) {
    particles.push_back(particle);
}
