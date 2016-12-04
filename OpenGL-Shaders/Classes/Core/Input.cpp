#include "Input.h"
#include <cstdio>
#include <iostream>

GLFWwindow* Input::window = NULL;
float Input::scroll;
glm::vec2 Input::mousePosition;

void Input::HandleInput(Window* window) {
	if (Input::window != NULL) {
		glfwSetScrollCallback(Input::window, NULL);
	}

	Input::window = window->GetGLFWWindow();
	glfwSetScrollCallback(Input::window, ScrollCallback);
	glfwSetCursorPosCallback(Input::window, CursorPositionCallback);
}
void Input::Clear() {
	scroll = 0.0f;
}

bool Input::GetKey(int key) {
	return glfwGetKey(window, key) != 0;
}
bool Input::GetMouseButton(int button) {
	return glfwGetMouseButton(window, button) != 0;
}
float Input::GetScroll() {
	return scroll;
}
glm::vec2 Input::GetMousePosition() {
	return mousePosition;
}

void Input::ScrollCallback(GLFWwindow* window, double xOffSet, double yOffSet) {
	scroll = (float)yOffSet;
}
void Input::CursorPositionCallback(GLFWwindow* window, double x, double y) {
	mousePosition.x = (float)x, mousePosition.y = (float)y;
}