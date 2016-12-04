#pragma once

#include <unordered_map>
#include <glm\glm.hpp>
#include "Window.h"

class Input {
private:
	static GLFWwindow* window;

	static float scroll;
	static glm::vec2 mousePosition;

	static void ScrollCallback(GLFWwindow* window, double xOffSet, double yOffSet);
	static void CursorPositionCallback(GLFWwindow* window, double x, double y);

public:
	static void HandleInput(Window* window);
	static void Clear();

	static bool GetKey(int key);
	static bool GetMouseButton(int button);
	static float GetScroll();
	static glm::vec2 GetMousePosition();
};