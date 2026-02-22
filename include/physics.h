#pragma once
#include <vector>
#include "object.h"

namespace Physics {
    const float G = 6.674e-2f;  // viel größer als real, aber sieht besser aus

    void update(std::vector<Object>& objects, float dt);

    void borderCollision(std::vector<Object>& objects, float width, float height);

    void objectCollision(std::vector<Object>& objects);
}