#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

Camera::Camera() {
	SetPerspective(45.0f, 1.0f);
	InitViewMatrix();
}
Camera::Camera(Projection projection, float size, float aspectRatio, float nearClip, float farClip) {
	if (projection == Projection::Perspective) {
		SetPerspective(size, aspectRatio, nearClip, farClip);
	} else {
		SetOrthographic(size, aspectRatio, nearClip, farClip);
	}
	InitViewMatrix();
}
void Camera::InitViewMatrix() {
	position = glm::vec3(0, 0, 0);
	front = glm::vec3(0, 0, 1);
	worldUp = glm::vec3(0, 1, 0);
	yaw = 90.0f;
	pitch = 0.0f;
	UpdateVectors();
}

Projection Camera::GetProjectionType() {
	return projectionType;
}
glm::mat4 Camera::GetProjectionMatrix() {
	return projectionMatrix;
}
void Camera::SetPosition(glm::vec3 position) {
	this->position = position;
	viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
}
glm::vec3 Camera::GetPosition() {
	return position;
}
glm::vec3 Camera::GetFront() {
	return front;
}
glm::vec3 Camera::GetUp() {
	return up;
}
glm::vec3 Camera::GetRight() {
	return right;
}
void Camera::SetPitch(float pitch) {
	this->pitch = pitch;
	UpdateVectors();
}
float Camera::GetPitch() {
	return pitch;
}
void Camera::SetYaw(float yaw) {
	this->yaw = yaw;
	UpdateVectors();
}
float Camera::GetYaw() {
	return yaw;
}
void Camera::UpdateVectors() {
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

	viewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);
}
glm::mat4 Camera::GetViewMatrix() {
	return viewMatrix;
}

float Camera::GetOrthographicSize() {
	return orthographicSize;
}
void Camera::SetOrthographicSize(float orthographicSize) {
	if (projectionType == Projection::Orthographic) {
		SetPerspective(orthographicSize, aspectRatio, nearClip, farClip);
	}
}
float Camera::GetFieldOfView() {
	return fieldOfView;
}
void Camera::SetFieldOfView(float fov) {
	if (projectionType == Projection::Perspective) {
		SetPerspective(fov, aspectRatio, nearClip, farClip);
	}
}
float Camera::GetAspectRatio() {
	return aspectRatio;
}
void Camera::SetAspectRatio(float aspectRatio) {
	this->aspectRatio = aspectRatio;
	ResetCamera();
}
float Camera::GetNearClip() {
	return nearClip;
}
void Camera::SetNearClip(float nearClip) {
	this->nearClip = nearClip;
	ResetCamera();
}
float Camera::GetFarClip() {
	return farClip;
}
void Camera::SetFarClip(float farClip) {
	this->farClip = farClip;
	ResetCamera();
}

void Camera::ResetCamera() {
	if (projectionType == Projection::Perspective) {
		SetPerspective(fieldOfView, aspectRatio, nearClip, farClip);
	} else {
		SetOrthographic(orthographicSize, aspectRatio, nearClip, farClip);
	}
}
void Camera::SetOrthographic(float orthographicSize, float aspectRatio, float nearClip, float farClip) {
	this->projectionType = Projection::Orthographic;
	this->orthographicSize = orthographicSize;
	this->aspectRatio = aspectRatio;
	this->nearClip = nearClip;
	this->farClip = farClip;
	
	float left, right, bottom, top;
	left = -orthographicSize * aspectRatio;
	right = orthographicSize * aspectRatio;
	bottom = -orthographicSize;
	top = orthographicSize;

	projectionMatrix = glm::ortho(left, right, bottom, top, nearClip, farClip);
}
void Camera::SetPerspective(float fieldOfView, float aspectRatio, float nearClip, float farClip) {
	this->projectionType = Projection::Perspective;
	this->fieldOfView = fieldOfView;
	this->aspectRatio = aspectRatio;
	this->nearClip = nearClip;
	this->farClip = farClip;

	projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearClip, 10000.0f);
	//projectionMatrix = glm::infinitePerspective(fieldOfView, aspectRatio, nearClip);
}