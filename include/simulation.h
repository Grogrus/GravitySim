#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "physics.h"

class Simulation {
public:
    Simulation(float width, float height);
    ~Simulation();

    void start();
    void addObject(Object obj);

private:
    float width, height;
    GLFWwindow* window;
    std::vector<Object> objects;

    void update(float dt);
    void draw() const;
};