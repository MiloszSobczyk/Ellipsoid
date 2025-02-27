#pragma once
#include <GLFW/glfw3.h>


class Window
{
private:
	GLFWwindow* nativeWindow;
	int width, height;
	const char* title;
public:
	Window(int width, int height, const char* title);
	~Window();

	void Update();
	bool ShouldClose();
	GLFWwindow* GetNativeWindow() const { return nativeWindow; }
};