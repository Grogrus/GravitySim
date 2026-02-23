#include "physics.h"
#include <glm/glm.hpp>

namespace Physics {

    void update(std::vector<Object>& objects, float dt) {
    // Kräfte zurücksetzen
    for (Object& obj : objects)
        obj.force = glm::vec3(0.0f);

    // Kräfte berechnen
    for (int i = 0; i < objects.size(); i++) {
        for (int j = i + 1; j < objects.size(); j++) {
            Object& a = objects[i];
            Object& b = objects[j];
            glm::vec3 diff = b.position - a.position;
            float dist = glm::length(diff);
            if (dist < 1.0f) continue;
            float force = G * a.mass * b.mass / (dist * dist);
            glm::vec3 dir = glm::normalize(diff);
            a.force += dir * force;
            b.force -= dir * force;
        }
    }

    // Leapfrog: erst alle velocities, dann alle positionen
    for (Object& obj : objects) {
        obj.velocity += (obj.force / obj.mass) * dt;
        obj.update(dt);
    }
}

    void borderCollision(std::vector<Object>& objects, float width, float height) {
        for (Object& obj : objects) {
            if (obj.position.x - obj.radius < 0.0f) {
                obj.position.x = obj.radius;
                obj.velocity.x *= -1.0f;
            }
            if (obj.position.x + obj.radius > width) {
                obj.position.x = width - obj.radius;
                obj.velocity.x *= -1.0f;
            }
            if (obj.position.y - obj.radius < 0.0f) {
                obj.position.y = obj.radius;
                obj.velocity.y *= -1.0f;
            }
            if (obj.position.y + obj.radius > height) {
                obj.position.y = height - obj.radius;
                obj.velocity.y *= -1.0f;
            }
        }
    }

    void objectCollision(std::vector<Object>& objects) {
        for (int i = 0; i < objects.size(); i++) {
            for (int j = i + 1; j < objects.size(); j++) {
                Object& a = objects[i];
                Object& b = objects[j];

                float dist = glm::length(b.position - a.position);
                if (dist >= a.radius + b.radius) continue;

                // Impulserhaltung: v_neu = (m1*v1 + m2*v2) / (m1+m2)
                glm::vec3 newVel = (a.mass * a.velocity + b.mass * b.velocity)
                                 / (a.mass + b.mass);

                if (a.mass >= b.mass) {
                    a.mass    += b.mass;
                    a.radius   = RADIUS_BASE + std::log(a.mass) * RADIUS_SCALE;
                    a.velocity = newVel;
                    objects.erase(objects.begin() + j);
                    j--;
                } else {
                    b.mass    += a.mass;
                    b.radius   = RADIUS_BASE + std::log(b.mass) * RADIUS_SCALE;
                    b.velocity = newVel;
                    objects.erase(objects.begin() + i);
                    i--;
                    break;
                }
            }
        }
    }
}