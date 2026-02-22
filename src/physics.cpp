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

            float radiusA = 10.0f + std::log(a.mass) * 2.0f;
            float radiusB = 10.0f + std::log(b.mass) * 2.0f;

            glm::vec3 diff = b.position - a.position;
            float dist = glm::length(diff);

            if (dist < radiusA + radiusB) {
                // Objekte auseinanderschieben damit sie nicht überlappen
                glm::vec3 dir = glm::normalize(diff);
                float overlap = (radiusA + radiusB) - dist;
                a.position -= dir * (overlap * 0.5f);
                b.position += dir * (overlap * 0.5f);

                // Velocities tauschen (elastischer Stoß, massebezogen)
                glm::vec3 relVel = b.velocity - a.velocity;
                float velAlongDir = glm::dot(relVel, dir);

                // Nur reagieren wenn sie aufeinander zubewegen
                if (velAlongDir > 0) continue;

                float impulse = (2.0f * velAlongDir) / (a.mass + b.mass);
                a.velocity += impulse * b.mass * dir;
                b.velocity -= impulse * a.mass * dir;
            }
        }
    }
}

}