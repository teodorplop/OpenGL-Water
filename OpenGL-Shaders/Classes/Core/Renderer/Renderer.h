#pragma once

#include "../Camera.h"
#include "Renderable.h"
#include <set>

class Renderer {
	Camera* camera;
	std::set<Renderable*> renderables;
	bool clipPlaneEnabled;
	glm::vec4 clipPlane;
public:
	Renderer(Camera* camera);
	~Renderer();

	void EnableClipPlane(glm::vec4 clipPlane);
	void DisableClipPlane();

	void Register(Renderable* renderable);
	void Unregister(Renderable* renderable);
	void Render();
};