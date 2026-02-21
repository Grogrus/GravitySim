#pragma once
#include <vector>
#include "object.h"

namespace Physics {
    const float G = 6.674e-11f;  // Gravitationskonstante

    void update(std::vector<Object>& objects, float dt);

    void borderCollision(std::vector<Object>& objects, float width, float height);
}