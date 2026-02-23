#include "object.h"
#include <glad/glad.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Object::Object(const std::string& name, float mass, glm::vec3 position,
               glm::vec3 velocity, glm::vec3 color)
    : name(name), mass(mass), radius(RADIUS_BASE + std::log(mass) * RADIUS_SCALE),
      position(position), velocity(velocity), color(color)
{}

void Object::update(float dt) {
    trailTimer += dt;
    if (trailTimer >= TRAIL_INTERVAL) {  // nur alle X Sekunden einen Punkt
        trail.push_back(position);
        if (trail.size() > TRAIL_LENGTH)
            trail.pop_front();
        trailTimer = 0.0f;
    }
    position += velocity * dt;
}

void Object::draw() const {
    // Trail: älter = transparenter
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < trail.size(); i++) {
        float alpha = 0.3f + 0.7f * ((float)i / trail.size());
        glColor4f(color.r, color.g, color.b, alpha);
        glVertex2f(trail[i].x, trail[i].y);
    }
    glEnd();

    // Kreis
    const int segments = CIRCLE_SEGMENTS;
    glColor4f(color.r, color.g, color.b, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            glVertex2f(position.x + radius * std::cos(angle),
                       position.y + radius * std::sin(angle));
        }
    glEnd();

    // Kraftvektor (gelb), Länge fix damit er immer sichtbar ist
    float forceLen = glm::length(force);
    if (forceLen > 0.01f) {
        glm::vec3 dir = glm::normalize(force);
        glColor4f(1.0f, 1.0f, 0.0f, 0.8f);
        glBegin(GL_LINES);
            glVertex2f(position.x, position.y);
            glVertex2f(position.x + dir.x * 50.0f,
                       position.y + dir.y * 50.0f);
        glEnd();
    }
}