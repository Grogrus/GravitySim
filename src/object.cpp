#include "object.h"
#include <glad/glad.h>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Konstruktor und Methoden für Object
Object::Object(const std::string& name,
               float mass,
               glm::vec3 position,
               glm::vec3 velocity,
               glm::vec3 color)
    : name(name), mass(mass), radius(10.0f + std::log(mass) * 2.0f),
      position(position), velocity(velocity), color(color)
{}


void Object::update(float dt) {
    trail.push_back(position);
    if (trail.size() > TRAIL_LENGTH) {
        trail.pop_front();
    }
    position += velocity * dt;
}

// Einfache Kreis-Rendering-Funktion
void Object::draw() const {
    // Trail zeichnen
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < trail.size(); i++) {
        float alpha = (float)i / trail.size(); // 0 = alt/transparent, 1 = neu
        glColor4f(color.r, color.g, color.b, alpha);
        glVertex2f(trail[i].x, trail[i].y);
    }
    glEnd();

    // Objekt zeichnen
    const int segments = 64;
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y);
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            glVertex2f(position.x + radius * std::cos(angle),
                       position.y + radius * std::sin(angle));
        }
    glEnd();

    // Kraftvektor zeichnen
    float forceLen = glm::length(force);
    if (forceLen > 0.01f) {
        glm::vec3 forceDir = glm::normalize(force);
        float scale = 50.0f / forceLen * forceLen; // Länge skaliert
        glColor4f(1.0f, 1.0f, 0.0f, 0.8f); // gelb
        glBegin(GL_LINES);
            glVertex2f(position.x, position.y);
            glVertex2f(position.x + forceDir.x * scale,
                    position.y + forceDir.y * scale);
        glEnd();
    }
}