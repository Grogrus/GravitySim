#include "simulation.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdexcept>

Simulation::Simulation(float width, float height)
    : width(width), height(height), ui(objects, paused, timeScale) {

    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                              "Gravity Simulation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));

    // 2D Koordinatensystem: 0,0 oben links
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ImGui initialisieren
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

Simulation::~Simulation() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Simulation::addObject(const Object& obj) {
    objects.push_back(obj);
}

void Simulation::update(float dt) {
    const int substeps = 10;
    float subDt = dt / substeps;
    for (int i = 0; i < substeps; i++) {
        Physics::update(objects, subDt);
        Physics::objectCollision(objects);
    }
}

void Simulation::draw() const {
    for (const Object& obj : objects)
        obj.draw();
}

void Simulation::start() {
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime) * timeScale;
        lastTime = currentTime;

        if (!paused)
        update(dt);

        glClear(GL_COLOR_BUFFER_BIT);
        draw();

        // ImGui Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ui.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}