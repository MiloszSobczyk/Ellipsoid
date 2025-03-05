#include "UserInterface.h"


UserInterface::UserInterface(Window* window)
	: window(window), flags(0), width(200.f), sliderValue(1.0f)
{
    flags |= ImGuiWindowFlags_NoTitleBar;
    flags |= ImGuiWindowFlags_NoMove;
    flags |= ImGuiWindowFlags_NoResize;
    flags |= ImGuiWindowFlags_NoCollapse;
    flags |= ImGuiWindowFlags_NoDocking;
}

void UserInterface::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos(ImVec2(window->GetWidth() - width, 0));
    ImGui::SetNextWindowSize(ImVec2(width, window->GetHeight()));
    ImGui::SetNextWindowBgAlpha(1.0f);

    RenderComponents();

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UserInterface::RenderComponents()
{
    ImGui::Begin("Hello, ImGui!", nullptr, flags);

    ImGui::SliderFloat("a", &sliderValue, 1.0f, 5.0f, "Value = %.2f");
}

