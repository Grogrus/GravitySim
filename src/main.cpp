#include "simulation.h"

int main() {
    Simulation sim(800.0f, 600.0f);

    sim.addObject(Object("A", 5000.0f,  glm::vec3(400, 300, 0), glm::vec3(0, 30, 0),   glm::vec3(0.2f, 0.5f, 1.0f)));
    sim.addObject(Object("B", 500.0f,   glm::vec3(550, 300, 0), glm::vec3(0, -150, 0), glm::vec3(0.8f, 0.8f, 0.8f)));
    sim.addObject(Object("C", 1000.0f,  glm::vec3(200, 200, 0), glm::vec3(80, 60, 0),  glm::vec3(1.0f, 0.4f, 0.2f)));
    sim.addObject(Object("D", 800.0f,   glm::vec3(600, 500, 0), glm::vec3(-60, 40, 0), glm::vec3(0.4f, 1.0f, 0.4f)));
    sim.addObject(Object("E", 300.0f,   glm::vec3(300, 500, 0), glm::vec3(50, -80, 0), glm::vec3(1.0f, 1.0f, 0.2f)));
    sim.start();
    return 0;
}