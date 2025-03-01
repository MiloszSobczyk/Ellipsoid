#pragma once

#include "Utils/Init.h"
#include "Window.h"
#include "Ellipsoid.h"

#include <string>

class App
{
private:
	Window window;
	bool active;
	Ellipsoid shape;

public:
	App(int windowWidth = 640, int windowHeight = 480, std::string title = "Pierce the Heavens");
	~App();

	void Run();
};