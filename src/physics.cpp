#include "physics.h"
#include <glm/glm.hpp>

namespace Physics {

    // Berechnet die Gravitationskräfte zwischen allen Objekten und aktualisiert deren Positionen
    void update(std::vector<Object>& objects, float dt) {
        // Gravitationskraft zwischen je zwei Objekten berechnen
        for (int i = 0; i < objects.size(); i++) {
            for (int j = i + 1; j < objects.size(); j++) {
                Object& a = objects[i];
                Object& b = objects[j];

                glm::vec3 diff = b.position - a.position;
                float dist = glm::length(diff);

                // Mindestabstand um Division durch 0 / extreme Kräfte zu vermeiden
                if (dist < 1.0f) continue;

                // F = G * m1 * m2 / r^2
                float force = G * a.mass * b.mass / (dist * dist);

                // Kraftrichtung normalisieren, dann auf Velocity anwenden
                glm::vec3 dir = glm::normalize(diff);

                // a = F / m  →  v += a * dt
                a.velocity += dir * (force / a.mass) * dt;
                b.velocity -= dir * (force / b.mass) * dt;
            }
        }

        // Positionen updaten
        for (Object& obj : objects) {
            obj.update(dt);
        }
    }

    //Kleine Funktion, um Kollisionen mit den Bildschirmrändern zu behandeln
    void borderCollision(std::vector<Object>& objects, float width, float height) {
    for (Object& obj : objects) {
        float radius = 10.0f + std::log(obj.mass) * 2.0f;

        if (obj.position.x - radius < 0.0f) {
            obj.position.x = radius;
            obj.velocity.x *= -1.0f;
        }
        if (obj.position.x + radius > width) {
            obj.position.x = width - radius;
            obj.velocity.x *= -1.0f;
        }
        if (obj.position.y - radius < 0.0f) {
            obj.position.y = radius;
            obj.velocity.y *= -1.0f;
        }
        if (obj.position.y + radius > height) {
            obj.position.y = height - radius;
            obj.velocity.y *= -1.0f;
        }
    }
}

void objectCollision(std::vector<Object>& objects) {
    for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            Object& a = objects[i];
            Object& b = objects[j];

            glm::vec3 diff = b.position - a.position;
            float dist = glm::length(diff);

            if (dist < a.radius + b.radius) {
                // Impulserhaltung: p = m*v, neues v = (m1*v1 + m2*v2) / (m1+m2)
                glm::vec3 newVelocity = (a.mass * a.velocity + b.mass * b.velocity)
                                       / (a.mass + b.mass);

                // Größeres Objekt absorbiert kleineres
                if (a.mass >= b.mass) {
                    a.mass   += b.mass;
                    a.radius  = 10.0f + std::log(a.mass) * 2.0f;
                    a.velocity = newVelocity;
                    objects.erase(objects.begin() + j);
                    j--; // Index korrigieren nach erase
                } else {
                    b.mass   += a.mass;
                    b.radius  = 10.0f + std::log(b.mass) * 2.0f;
                    b.velocity = newVelocity;
                    objects.erase(objects.begin() + i);
                    i--; // Index korrigieren nach erase
                    break; // a existiert nicht mehr
                }
            }
        }
    }
}

}