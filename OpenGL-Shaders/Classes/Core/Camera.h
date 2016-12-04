#pragma once

#include <glm\glm.hpp>
#include "Transform.h"

enum Projection {Orthographic, Perspective};

class Camera {
private:
	float aspectRatio, nearClip, farClip;
	// orthographic
	float orthographicSize;
	// perspective
	float fieldOfView;

	Projection projectionType;
	glm::mat4 projectionMatrix;

	glm::vec3 position, front, worldUp, up, right;
	float yaw, pitch;
	glm::mat4 viewMatrix;

	void InitViewMatrix();
	void UpdateVectors();

public:
	Camera();
	Camera(Projection projection, float size, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);

	Projection GetProjectionType();
	glm::mat4 GetProjectionMatrix();

	void SetPosition(glm::vec3 position);
	glm::vec3 GetPosition();
	glm::vec3 GetFront();
	glm::vec3 GetUp();
	glm::vec3 GetRight();

	void SetPitch(float pitch);
	float GetPitch();
	void SetYaw(float yaw);
	float GetYaw();
	glm::mat4 GetViewMatrix();

	float GetOrthographicSize();
	void SetOrthographicSize(float orthographicSize);
	float GetFieldOfView();
	void SetFieldOfView(float fov);
	float GetAspectRatio();
	void SetAspectRatio(float aspectRatio);
	float GetNearClip();
	void SetNearClip(float nearClip);
	float GetFarClip();
	void SetFarClip(float farClip);

private:
	void ResetCamera();
	void SetOrthographic(float size, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);
	void SetPerspective(float fieldOfView, float aspectRatio, float nearClip = 0.1f, float farClip = 1000.0f);
};