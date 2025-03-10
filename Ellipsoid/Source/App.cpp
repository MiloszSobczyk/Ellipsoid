#include "App.h"
#include <stdexcept>

App::App(int windowWidth, int windowHeight, std::string title)
	: window(windowWidth, windowHeight, title), active(true), shape(1.f, 1.f, 1.f), UI(&window)
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

        rayCaster.CalculatePoints(shape, window, 2);
        rayCaster.Render();

        UI.Render();

        window.Update();
    }
}
