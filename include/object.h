#pragma once
#include <string>
#include <glm/glm.hpp>
#include <deque>

struct Object {
    std::string name;
    float       mass;
    float       radius;
    glm::vec3   position;
    glm::vec3   velocity;
    glm::vec3   color;
    glm::vec3 force;
    std::deque<glm::vec3> trail;  // Vergangenheit der Positionen für den Trail
    static const int TRAIL_LENGTH = 500; // Maximale Länge des Trails

    Object(const std::string& name,
           float mass,
           glm::vec3 position,
           glm::vec3 velocity,
           glm::vec3 color);

    void update(float dt);
    void draw() const;
};