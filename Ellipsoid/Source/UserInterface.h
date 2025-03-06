#pragma once
#include <Window.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

struct UIValues
{
	float a;
	float b;
	float c;
	float scale;
	float translationX;
	float translationY;
	float translationZ;	
	float rotationX;
	float rotationY;
	float rotationZ;
};


class UserInterface
{
private:
	Window* window;
	ImGuiWindowFlags flags;
	float width;

	void HandleMouseDrag();

public:
	static UIValues values;

	UserInterface(Window* window);
	
	void Render();
	void RenderComponents();
};