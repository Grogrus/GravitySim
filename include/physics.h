#pragma once
#include <vector>
#include "object.h"

namespace Physics {
    const float G = 6.674e-3f; // Skalierte Gravitationskonstante für die Simulation

    void update(std::vector<Object>& objects, float dt);          // Gravitation + Bewegung
    void borderCollision(std::vector<Object>& objects, float width, float height);
    void objectCollision(std::vector<Object>& objects);           // Absorption bei Kollision
}