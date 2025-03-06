#include "UserInterface.h"

UIValues UserInterface::values{
    .a = 1.f,
    .b = 1.f,
    .c = 1.f,
    .scale = 1.f,
    .translationX = 0.f,
    .translationY = 0.f,
    .translationZ = 0.f,
    .rotationX = 0.0f,
    .rotationY = 0.0f,
    .rotationZ = 0.0f
};


void UserInterface::HandleMouseDrag()
{
    if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
    {
        ImVec2 mouseDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);

        values.translationX += mouseDelta.x * 0.01f;
        values.translationY -= mouseDelta.y * 0.01f;

        ImGui::ResetMouseDragDelta(ImGuiMouseButton_Right);
    }
}

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

    HandleMouseDrag();

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
        ImGui::SliderFloat("##a", &(values.a), 0.5f, 5.0f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("b");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##b", &(values.b), 0.5f, 5.0f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("c");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##c", &(values.c), 0.5f, 5.0f, "%.2f");

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

    ImGui::Text("Scale");

    if (ImGui::BeginTable("table3", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextColumn();
        ImGui::Text("s");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##scale", &(values.scale), 0.5f, 4.f, "%.2f");

        ImGui::EndTable();
    }

    ImGui::Text("Rotations");

    if (ImGui::BeginTable("table4", 2, ImGuiTableFlags_SizingStretchProp))
    {
        ImGui::TableNextColumn();
        ImGui::Text("X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##rx", &(values.rotationX), 0.f, 7.f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##ry", &(values.rotationY), 0.f, 7.f, "%.2f");

        ImGui::TableNextColumn();
        ImGui::Text("Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(-FLT_MIN);
        ImGui::SliderFloat("##rz", &(values.rotationZ), 0.f, 7.f, "%.2f");

        ImGui::EndTable();
    }
}

