#pragma once

#include "../Core/Tickable/ITickable.h"
#include "../Core/Renderer/Renderer.h"
#include "../Core/Renderer/Water/WaterRenderer.h"
#include "../Core/Camera.h"
#include "CameraController.h"

class GameManager : public ITickable {
	Camera* camera;
	CameraController* cameraController;

	Renderable* terrain;
	Water* water;

	Renderer* renderer;
	WaterRenderer* waterRenderer;

public:
	GameManager(Camera* camera);
	~GameManager();

	void Tick();
};
