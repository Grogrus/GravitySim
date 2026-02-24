#include "ui.h"
#include <glm/glm.hpp>

UI::UI(std::vector<Object>& objects, bool& paused, float& timeScale)
    : objects(objects), paused(paused), timeScale(timeScale) {}

void UI::draw() {
    drawControlPanel();
}

void UI::drawControlPanel() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(400, 600), ImGuiCond_Once);
    ImGui::Begin("Control Panel");

    drawSimControls();
    ImGui::Separator();
    drawObjectTable();
    ImGui::Separator();
    drawAddObject();

    ImGui::End();
}

void UI::drawSimControls() {
    ImGui::Text("Simulation");

    // Pause/Resume
    if (paused) {
        if (ImGui::Button("Resume")) paused = false;
    } else {
        if (ImGui::Button("Pause"))  paused = true;
    }

    ImGui::SameLine();

    // Reset
    if (ImGui::Button("Reset")) {
        objects.clear();
    }

    // TimeScale Slider
    ImGui::SliderFloat("Zeitskala", &timeScale, 1.0f, 1000.0f, "%.0fx");
}

void UI::drawObjectTable() {
    ImGui::Text("Objekte: %d", (int)objects.size());

    if (ImGui::BeginTable("objects", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Masse");
        ImGui::TableSetupColumn("Geschw.");
        ImGui::TableSetupColumn("##del");  // Spalte für Löschen-Button
        ImGui::TableHeadersRow();

        for (int i = 0; i < objects.size(); i++) {
            Object& obj = objects[i];
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::TextColored(ImVec4(obj.color.r, obj.color.g, obj.color.b, 1.0f),
                               "%s", obj.name.c_str());

            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%.2f", obj.mass);

            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.2f", glm::length(obj.velocity));

            ImGui::TableSetColumnIndex(3);
            ImGui::PushID(i);  // wichtig: sonst haben alle Buttons gleiche ID
            if (ImGui::SmallButton("X")) {
                objects.erase(objects.begin() + i);
                ImGui::PopID();
                break;  // nach erase nicht weiterlaufen
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

void UI::drawAddObject() {
    ImGui::Text("Neues Objekt:");

    static char name[64] = "";
    static float mass      = 100.0f;
    static float pos[2]   = {700.0f, 500.0f};
    static float vel[2]   = {0.0f, 0.0f};
    static float color[3] = {1.0f, 1.0f, 1.0f};

    ImGui::InputText("Name",     name, sizeof(name));
    ImGui::SliderFloat("Masse",  &mass, 0.1f, 10000.0f);
    ImGui::InputFloat2("Position", pos);
    ImGui::InputFloat2("Velocity", vel);
    ImGui::ColorEdit3("Farbe",   color);

    if (ImGui::Button("Hinzufügen")) {
        objects.push_back(Object(
            std::string(name),
            mass,
            glm::vec3(pos[0], pos[1], 0),
            glm::vec3(vel[0], vel[1], 0),
            glm::vec3(color[0], color[1], color[2])
        ));
    }
}