#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Vector4.h"
#include "Matrix4.h"

#include <iostream>
#include <EllipsoidSolver.h>

void RenderPoints(const EllipsoidSolver& solver)
{
    const auto& points = solver.getPoints();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < 750; ++i)
    {
        for (int j = 0; j < 1000; ++j)
        {
            float x = points[i][j].x;
            float y = points[i][j].y;
            if(points[i][j].z > 0)
                glVertex2f(x, y);
        }
    }
    glEnd();
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 750, "Ellipsoid Points", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
    }

    EllipsoidSolver solver(Ellipsoid(1.f, 1.f, 1.f), 1000, 750);
    solver.Solve(); 

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();

        RenderPoints(solver);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}
