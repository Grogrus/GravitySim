#pragma once
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "object.h"
#include "physics.h"

// Verwaltet das Fenster, die Game-Loop und alle Objekte
class Simulation {

    float timeScale = 1.0f; // 1.0 = Echtzeit, >1.0 = schneller, <1.0 = langsamer
public:
    Simulation(float width, float height);
    ~Simulation();

    void start();
    void addObject(const Object& obj);

private:
    float width, height;
    GLFWwindow* window;
    std::vector<Object> objects;

    void update(float dt);
    void draw() const;
};