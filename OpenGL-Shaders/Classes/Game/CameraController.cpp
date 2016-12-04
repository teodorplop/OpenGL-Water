#include "CameraController.h"
#include <GLFW\glfw3.h>

#include "../Core/Input.h"
#include "../Core/TimeFrame.h"

float CameraController::cameraSpeed = 100.0f;

CameraController::CameraController(Camera* camera) {
	this->camera = camera;
	this->lastMousePosition = glm::vec2(0, 0);
	this->speed = 5;
	this->firstMouse = true;
}

void CameraController::Tick() {
	glm::vec2 mousePosition = Input::GetMousePosition();
	if (firstMouse) {
		lastMousePosition = mousePosition;
		firstMouse = false;
	}

	glm::vec2 mouseMovement = mousePosition - lastMousePosition;

	glm::vec3 position = camera->GetPosition();
	glm::vec3 front = camera->GetFront();
	glm::vec3 right = camera->GetRight();
	float pitch = camera->GetPitch();
	float yaw = camera->GetYaw();

	if (Input::GetKey(GLFW_KEY_W)) {
		position += front * cameraSpeed * TimeFrame::deltaTime * 10.0f;
		camera->SetPosition(position);
	}
	if (Input::GetKey(GLFW_KEY_S)) {
		position -= front * cameraSpeed * TimeFrame::deltaTime * 10.0f;
		camera->SetPosition(position);
	}
	if (Input::GetKey(GLFW_KEY_A)) {
		position -= right * cameraSpeed * TimeFrame::deltaTime * 10.0f;
		camera->SetPosition(position);
	}
	if (Input::GetKey(GLFW_KEY_D)) {
		position += right * cameraSpeed * TimeFrame::deltaTime * 10.0f;
		camera->SetPosition(position);
	}
	if (Input::GetMouseButton(1)) {
		position.y += mouseMovement.y * cameraSpeed * TimeFrame::deltaTime;
		camera->SetPosition(position);
	}
	if (Input::GetMouseButton(0)) {
		pitch += mouseMovement.y * cameraSpeed * TimeFrame::deltaTime * 0.05f;
		pitch = glm::clamp(pitch, -89.0f, 89.0f);
		yaw += mouseMovement.x * cameraSpeed * TimeFrame::deltaTime * 0.05f;

		camera->SetPitch(pitch);
		camera->SetYaw(yaw);
	}

	lastMousePosition = mousePosition;
}
