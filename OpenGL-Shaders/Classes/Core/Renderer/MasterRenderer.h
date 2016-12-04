#pragma once

#include "Renderer.h"
#include "Water/WaterFrameBuffer.h"
#include "Water/WaterRenderer.h"

#include <set>

class MasterRenderer {
	static Camera* camera;

	static std::set<Renderer*> renderers;
	static WaterFrameBuffer* waterFrameBuffer;
	static std::set<WaterRenderer*> waterRenderers;

public:
	static void Initialize(Camera* camera);
	static void Register(Renderer* renderer);
	static void Unregister(Renderer* renderer);
	static void Register(WaterRenderer* waterRenderer);
	static void Unregister(WaterRenderer* waterRenderer);
	static void Render();
};
