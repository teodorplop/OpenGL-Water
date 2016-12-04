#pragma once

#include "../Core/Renderer/Renderer.h"
#include "../Core/Renderer/Water/WaterRenderer.h"
#include "../Core/Camera.h"
#include "CameraController.h"

class GameManager {
	Camera* camera;
	CameraController* cameraController;
	Renderer* renderer;
	WaterRenderer* waterRenderer;

public:
	GameManager(Camera* camera);
	~GameManager();
};
