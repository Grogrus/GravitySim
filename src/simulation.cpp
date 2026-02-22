#include "simulation.h"
#include <stdexcept>

Simulation::Simulation(float width, float height) : width(width), height(height) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                              "Gravity Simulation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Simulation::~Simulation() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Simulation::addObject(Object obj) {
    objects.push_back(obj);
}

void Simulation::update(float dt) {
    Physics::update(objects, dt);
    Physics::objectCollision(objects);
    Physics::borderCollision(objects, width, height);
}

void Simulation::draw() const {
    for (const Object& obj : objects) {
        obj.draw();
    }
}

void Simulation::start() {
    while (!glfwWindowShouldClose(window)) {
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        update(dt);

        glClear(GL_COLOR_BUFFER_BIT);
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}