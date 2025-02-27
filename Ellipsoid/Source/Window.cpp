#include "Window.h"
#include <stdexcept>

Window::Window(int width, int height, const char* title)
	: width(width), height(height), title(title)
{
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	nativeWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!nativeWindow)
	{
		throw std::runtime_error("Window creation failed");
	}

	glfwMakeContextCurrent(nativeWindow);
}

Window::~Window()
{
	glfwDestroyWindow(nativeWindow);
}

void Window::Update()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(nativeWindow);
	glfwPollEvents();
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(nativeWindow);
}

