#include "simulation.h"

/**
 * Hauptfunktion, die die Simulation initialisiert, Objekte hinzufügt und die Simulation startet.
 * @return int Rückgabewert des Programms, 0 bei erfolgreichem Abschluss
 */

int main() {
    Simulation sim(1400.0f, 1000.0f);

    float cx = 700.0f, cy = 500.0f;

    sim.addObject(Object("Sonne",   1989000.0f, glm::vec3(cx, cy, 0),        glm::vec3(0, 0, 0),      glm::vec3(1.0f, 0.9f, 0.2f)));
    sim.addObject(Object("Merkur",  0.33f,      glm::vec3(cx+58,  cy, 0),    glm::vec3(0, -15.13f, 0), glm::vec3(0.6f, 0.6f, 0.6f)));
    sim.addObject(Object("Venus",   4.87f,      glm::vec3(cx+108, cy, 0),    glm::vec3(0, -11.09f, 0), glm::vec3(0.9f, 0.7f, 0.3f)));
    sim.addObject(Object("Erde",    5.97f,      glm::vec3(cx+150, cy, 0),    glm::vec3(0,  -9.41f, 0), glm::vec3(0.2f, 0.5f, 1.0f)));
    sim.addObject(Object("Mars",    0.642f,     glm::vec3(cx+228, cy, 0),    glm::vec3(0,  -7.63f, 0), glm::vec3(0.8f, 0.3f, 0.1f)));
    sim.addObject(Object("Jupiter", 1898.0f,    glm::vec3(cx+400, cy, 0),    glm::vec3(0,  -5.76f, 0), glm::vec3(0.8f, 0.6f, 0.4f)));

    sim.start();
    return 0;
}