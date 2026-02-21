#pragma once
#include <string>
#include <glm/glm.hpp>

struct Object {
    std::string name;
    float       mass;
    glm::vec3   position;   // z = 0 in 2D
    glm::vec3   velocity;   // z = 0 in 2D
    glm::vec3   color;      // RGB, je 0.0 - 1.0

    // Konstruktor
    Object(const std::string& name,
           float mass,
           glm::vec3 position,
           glm::vec3 velocity,
           glm::vec3 color);

    void update(float dt);  // Position anhand Velocity weiterbewegen
    void draw() const;      // Kreis an Position rendern
};