#pragma once
#include <string>
#include <deque>
#include <glm/glm.hpp>

static const float RADIUS_BASE      = 10.0f;
static const float RADIUS_SCALE     = 2.0f;
static const int   CIRCLE_SEGMENTS  = 64;
static const float MIN_DIST         = 1.0f;
static const float FORCE_DRAW_SCALE = 50.0f;

// Repräsentiert einen Himmelskörper in der Simulation
struct Object {
    std::string name;
    float       mass;
    float       radius;     // Wird aus der Masse berechnet: RADIUS_BASE + log(mass)*RADIUS_SCALE
    glm::vec3   position;   // z=0 in 2D, vorbereitet für 3D
    glm::vec3   velocity;
    glm::vec3   force;      // Akkumulierte Gravitationskraft, wird jeden Frame zurückgesetzt
    glm::vec3   color;      // RGB, je 0.0 - 1.0

    std::deque<glm::vec3> trail;
    float trailTimer = 0.0f;  // ← Member der Struct, nicht global

    static const int   TRAIL_LENGTH    = 500;
    static constexpr float TRAIL_INTERVAL = 0.05f; // alle 50ms ein Punkt

    Object(const std::string& name, float mass, glm::vec3 position,
           glm::vec3 velocity, glm::vec3 color);

    void update(float dt);
    void draw() const;
};