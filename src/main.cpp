#include "simulation.h"
#include <array>

int main() {
    const float CENTER_X = 900.0f;
    const float CENTER_Y = 500.0f;
    const int   PLANET_COUNT = 6;

    enum class Planet { SUN, MERCURY, VENUS, EARTH, MARS, JUPITER };

    std::array<std::string, PLANET_COUNT> names = {
        "Sonne", "Merkur", "Venus", "Erde", "Mars", "Jupiter"
    };

    std::array<float, PLANET_COUNT> masses = {
        1989000.0f, 0.33f, 4.87f, 5.97f, 0.642f, 1898.0f
    };

    std::array<glm::vec3, PLANET_COUNT> positions = {
        glm::vec3(CENTER_X,       CENTER_Y, 0),  // Sonne
        glm::vec3(CENTER_X + 58,  CENTER_Y, 0),  // Merkur
        glm::vec3(CENTER_X + 108, CENTER_Y, 0),  // Venus
        glm::vec3(CENTER_X + 150, CENTER_Y, 0),  // Erde
        glm::vec3(CENTER_X + 228, CENTER_Y, 0),  // Mars
        glm::vec3(CENTER_X + 778, CENTER_Y, 0)   // Jupiter
    };

    std::array<glm::vec3, PLANET_COUNT> velocities = {
        glm::vec3(0,  0.00f, 0),  // Sonne
        glm::vec3(0, -15.13f, 0), // Merkur
        glm::vec3(0, -11.09f, 0), // Venus
        glm::vec3(0,  -9.41f, 0), // Erde
        glm::vec3(0,  -7.63f, 0), // Mars
        glm::vec3(0,  -4.13f, 0)  // Jupiter
    };

    std::array<glm::vec3, PLANET_COUNT> colors = {
        glm::vec3(1.0f, 0.9f, 0.2f), // Sonne
        glm::vec3(0.6f, 0.6f, 0.6f), // Merkur
        glm::vec3(0.9f, 0.7f, 0.3f), // Venus
        glm::vec3(0.2f, 0.5f, 1.0f), // Erde
        glm::vec3(0.8f, 0.3f, 0.1f), // Mars
        glm::vec3(0.8f, 0.6f, 0.4f)  // Jupiter
    };

    Simulation sim(1800.0f, 1000.0f);

    for (int i = 0; i < PLANET_COUNT; i++) {
        sim.addObject(Object(names[i], masses[i], positions[i], velocities[i], colors[i]));
    }

    sim.start();
    return 0;
}