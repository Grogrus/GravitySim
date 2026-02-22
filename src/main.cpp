#include "simulation.h"

int main() {
    Simulation sim(800.0f, 600.0f);

    sim.addObject(Object("A", 5000.0f, glm::vec3(400, 300, 0), glm::vec3(0, 5, 0),     glm::vec3(0.2f, 0.5f, 1.0f)));
    sim.addObject(Object("B", 500.0f,  glm::vec3(550, 300, 0), glm::vec3(0, -20, 0),   glm::vec3(0.8f, 0.8f, 0.8f)));
    sim.addObject(Object("C", 1000.0f, glm::vec3(200, 200, 0), glm::vec3(10, 8, 0),    glm::vec3(1.0f, 0.4f, 0.2f)));
    sim.addObject(Object("D", 800.0f,  glm::vec3(600, 500, 0), glm::vec3(-8, 5, 0),    glm::vec3(0.4f, 1.0f, 0.4f)));
    sim.addObject(Object("E", 300.0f,  glm::vec3(300, 500, 0), glm::vec3(6, -10, 0),   glm::vec3(1.0f, 1.0f, 0.2f)));
    sim.addObject(Object("F", 200.0f,  glm::vec3(150, 400, 0), glm::vec3(12, -5, 0),   glm::vec3(1.0f, 0.2f, 0.8f)));
    sim.addObject(Object("G", 400.0f,  glm::vec3(650, 150, 0), glm::vec3(-10, 15, 0),  glm::vec3(0.2f, 1.0f, 1.0f)));
    sim.addObject(Object("H", 600.0f,  glm::vec3(100, 550, 0), glm::vec3(15, -8, 0),   glm::vec3(1.0f, 0.6f, 0.2f)));
    sim.addObject(Object("I", 250.0f,  glm::vec3(700, 400, 0), glm::vec3(-5, -12, 0),  glm::vec3(0.6f, 0.2f, 1.0f)));
    sim.addObject(Object("J", 350.0f,  glm::vec3(450, 100, 0), glm::vec3(-8, 18, 0),   glm::vec3(1.0f, 1.0f, 0.6f)));

    sim.start();
    return 0;
}