#include "testgui.h"
#include "game.h"
#include "imgui/animation_curve.h"
#include "lightpos.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

BezierEditor TestGUI::editor;
std::vector<BezierKeyframe> TestGUI::myCurve;
std::vector<BezierKeyframe> TestGUI::previousCurve;

void TestGUI::init(const Window &window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(
            window.window,
            true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    myCurve = {
            {0.0f, 0.0f, ImVec2(30, 0)}, // Start: time=0, value=0, handle right
            {0.25f, 0.5f, ImVec2(40, 10)}, // Slight upward curve
            {0.5f, 0.2f, ImVec2(30, -20)}, // Dip
            {0.75f, 0.8f, ImVec2(20, 20)}, // Rise
            {1.0f, 1.0f, ImVec2(30, 0)} // End: time=1, value=1, flat out
    };

    editor = BezierEditor(window.window); // pass GLFWwindow*
}

void TestGUI::initializeFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Light Editor");

    for (size_t i = 0; i < global_lights.size(); ++i) {
        ImGui::PushID(static_cast<int>(i)); // Unique ID for ImGui

        ImGui::Text("Light %d", static_cast<int>(i));
        ImGui::SliderFloat3("Position", &global_lights[i].position.x, -20.0f, 20.0f);
        ImGui::ColorEdit3("Color", &global_lights[i].color.x);

        if (ImGui::Button("Remove Light")) {
            global_lights.erase(global_lights.begin() + i);
            ImGui::PopID();
            break; // Break to avoid iterator invalidation
        }

        ImGui::Separator();
        ImGui::PopID();
    }

    ImGui::SliderFloat2("Offset Position", &Game::perlinOffset.x, -100.0f, 100.0f);
    ImGui::InputInt("Seed", &Game::seed);

    auto m_meshResolution = static_cast<int>(Game::meshResolution);
    ImGui::InputInt("Resolution", &m_meshResolution);
    Game::meshResolution = static_cast<unsigned int>(m_meshResolution);

    ImGui::SliderFloat("Scale", &Game::scale, 0.0f, 30.0f);
    ImGui::SliderFloat("Height Multiplier", &Game::heightMultiplier, 0.0f, 30.0f);

    ImGui::InputInt("Octaves", &Game::octaves);
    ImGui::SliderFloat("Persistence", &Game::persistence, 0.0f, 3.0f);
    ImGui::SliderFloat("Lacunarity", &Game::lacunarity, 0.0f, 3.0f);
    ImGui::SliderFloat3("Position", &Game::perlinPosition.x, -30.0f, 30.0f);

    if (auto temp = static_cast<int>(Game::sizeOfMesh); ImGui::InputInt("Mesh Size: ", &temp)) {
        if (temp < 0)
            temp = 0; // Clamp to 0 to avoid negative values
        Game::sizeOfMesh = static_cast<unsigned int>(temp);
    }

    if (ImGui::Button("Add Light")) {
        global_lights.emplace_back(glm::vec3(0.0f), glm::vec3(1.0f));
    }

    ImGui::End();

    ImGui::Begin("Editor");

    editor.Draw("My Bezier Curve", myCurve);

    ImGui::End();
}

void TestGUI::renderGUI() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
