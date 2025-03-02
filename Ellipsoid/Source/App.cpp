#include "App.h"
#include <stdexcept>

App::App(int windowWidth, int windowHeight, std::string title)
	: window(windowWidth, windowHeight, title), active(true), shape(1.f, 1.f, 1.f)
{
    active &= InitImgui(window.GetNativeWindow());
    if (!active)
    {
        throw std::runtime_error("cannot initialize app");
    }
}

App::~App()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void App::Run()
{
    while (active && !window.ShouldClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        rayCaster.CalculatePoints(shape, window, 16);
        rayCaster.Render();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a test window.");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.Update();
    }
}
