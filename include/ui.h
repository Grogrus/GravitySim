#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "object.h"
#include "imgui.h"

class UI {
public:
    UI(std::vector<Object>& objects, bool& paused, float& timeScale);
    void draw();

private:
    std::vector<Object>& objects;
    bool&  paused;
    float& timeScale;

    void drawControlPanel();
    void drawObjectTable();
    void drawAddObject();
    void drawSimControls();  
};