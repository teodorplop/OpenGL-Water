#pragma once

#include <glm\glm.hpp>
#include "..\Core\Tickable\ITickable.h"
#include "..\Core\Camera.h"

class CameraController : public ITickable {
public:
	CameraController(Camera* camera);

private:
	static float cameraSpeed;
	bool firstMouse;
	glm::vec2 lastMousePosition;
	float speed;
	Camera* camera;

protected:
	void Tick();
};
