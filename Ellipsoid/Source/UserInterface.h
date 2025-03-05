#pragma once
#include <Window.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


class UserInterface
{
private:
	Window* window;
	ImGuiWindowFlags flags;
	float width;
	float sliderValue;

public:
	UserInterface(Window* window);
	
	void Render();
	void RenderComponents();
};