#include "UserInterface.h"

UIValues UserInterface::values{
    .a = 1.f,
    .b = 1.f,
    .c = 1.f,
    .scale = 1.f,
    .translationX = 0.f,
    .translationY = 0.f,
    .translationZ = 0.f,
};


UserInterface::UserInterface(Window* window)
	: window(window), flags(0), width(200.f)
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

    ImGui::Text("Ellipse parameters");

    if (ImGui::BeginTable("table1", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextColumn();
        ImGui::Text("a");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##a", &(values.a), 1.0f, 5.0f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("b");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##b", &(values.b), 1.0f, 5.0f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("c");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##c", &(values.c), 1.0f, 5.0f, "%.2f");

        ImGui::EndTable();
    }

    ImGui::Text("Translations");

    if (ImGui::BeginTable("table2", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextColumn();
        ImGui::Text("X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##x", &(values.translationX), -10.f, 10.f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##y", &(values.translationY), -10.f, 10.f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##z", &(values.translationZ), -10.f, 10.f, "%.2f");

        ImGui::EndTable();
    }

}

