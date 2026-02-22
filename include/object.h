#pragma once
#include <string>
#include <glm/glm.hpp>

struct Object {
    std::string name;
    float       mass;
    float       radius;     // ← neu
    glm::vec3   position;
    glm::vec3   velocity;
    glm::vec3   color;

    Object(const std::string& name,
           float mass,
           glm::vec3 position,
           glm::vec3 velocity,
           glm::vec3 color);

    void update(float dt);
    void draw() const;
};