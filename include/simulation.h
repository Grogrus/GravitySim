#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "physics.h"
#include "ui.h"

class Simulation {
public:
    Simulation(float width, float height);
    ~Simulation();

    void start();
    void addObject(const Object& obj);

private:
    float width, height;
    float timeScale = 1.0f;
    bool paused = false;
    GLFWwindow* window;
    std::vector<Object> objects;
    UI ui;

    void update(float dt);
    void draw() const;
};