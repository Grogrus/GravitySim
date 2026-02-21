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
    : name(name), mass(mass), position(position), velocity(velocity), color(color)
{}


void Object::update(float dt) {
    position += velocity * dt;
}

// Einfache Kreis-Rendering-Funktion
void Object::draw() const {
    const int segments = 64;
    float radius = 10.0f + std::log(mass) * 2.0f; // Größe basierend auf Masse

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(position.x, position.y); // Mittelpunkt
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            glVertex2f(position.x + radius * std::cos(angle),
                       position.y + radius * std::sin(angle));
        }
    glEnd();
}