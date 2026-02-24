#include "ui.h"
#include <glm/glm.hpp>

UI::UI(std::vector<Object>& objects, bool& paused, float& timeScale)
    : objects(objects), paused(paused), timeScale(timeScale) {}

void UI::draw() {
    drawControlPanel();
}

void UI::drawControlPanel() {
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(420, 600), ImGuiCond_Once);
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

    if (paused) {
        if (ImGui::Button("Resume")) paused = false;
    } else {
        if (ImGui::Button("Pause"))  paused = true;
    }

    ImGui::SameLine();

    if (ImGui::Button("Reset"))
        objects.clear();

    ImGui::SliderFloat("Zeitskala", &timeScale, 1.0f, 1000.0f, "%.0fx");
}

void UI::drawObjectTable() {
    ImGui::Text("Objekte: %d", (int)objects.size());

    if (ImGui::BeginTable("objects", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Masse");
        ImGui::TableSetupColumn("Geschw.");
        ImGui::TableSetupColumn("##del");
        ImGui::TableHeadersRow();

        for (int i = 0; i < (int)objects.size(); i++) {
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
            ImGui::PushID(i);
            if (ImGui::SmallButton("X")) {
                objects.erase(objects.begin() + i);
                ImGui::PopID();
                break;
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
}

void UI::drawAddObject() {
    ImGui::Text("Neues Objekt:");
    ImGui::TextDisabled("1 px = 1 Mio km  |  Erde = 5.97  |  Sonne = 1989000");

    static char  name[64]  = "";
    static float mass      = 5.97f;
    static float pos[2]    = {700.0f, 500.0f};
    static float vel[2]    = {0.0f, 0.0f};
    static float color[3]  = {1.0f, 1.0f, 1.0f};

    ImGui::InputText("Name",                    name, sizeof(name));
    ImGui::InputFloat("Masse (x10^24 kg)",      &mass);
    ImGui::InputFloat2("Position X/Y (px)",     pos);
    ImGui::InputFloat2("Velocity X/Y (px/s)",   vel);
    //ImGui::TextDisabled("  X: links(-) / rechts(+)");
    //ImGui::TextDisabled("  Y: oben(-)  / unten(+)");
    //ImGui::TextDisabled("  Orbitalgeschw. v = sqrt(G * M / r)");
    ImGui::ColorEdit3("Farbe", color);

    if (ImGui::Button("Hinzufuegen")) {
        objects.push_back(Object(
            std::string(name),
            mass,
            glm::vec3(pos[0], pos[1], 0),
            glm::vec3(vel[0], vel[1], 0),
            glm::vec3(color[0], color[1], color[2])
        ));
    }
}