#pragma once

#include <glm\glm.hpp>

class Light {
public:
	static glm::vec3 position;
	static glm::vec3 color;
	static float intensity;
	static glm::vec3 direction;
};