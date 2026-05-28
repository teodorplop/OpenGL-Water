#pragma once

#include "../../Camera.h"
#include "Water.h"
#include "WaterFrameBuffer.h"
#include <set>

class WaterRenderer {
private:
	Camera* camera;
	std::set<Water*> waters;

public:
	WaterRenderer(Camera* camera);
	~WaterRenderer();

	void Register(Water* water);
	void Unregister(Water* water);

	void Render(WaterFrameBuffer* waterFrameBuffer);
};