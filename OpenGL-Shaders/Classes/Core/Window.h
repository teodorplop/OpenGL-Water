#pragma once

#include <GLFW\glfw3.h>

class Window {
public:
	static int windowWidth, windowHeight;

private:
	const char* title;
	int width, height;
	GLFWwindow* window;

	bool Init();

public:
	Window(const char* title, int width, int height);
	~Window();
	void Update();
	bool Closed();

	int GetWidth();
	int GetHeight();
	GLFWwindow* GetGLFWWindow();
};

