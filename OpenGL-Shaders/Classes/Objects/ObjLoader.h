#pragma once

#include <glm\glm.hpp>
#include <GL/freeglut.h>
#include <string>
#include <vector>

class ObjLoader {
private:
	struct PackedVertex {
		glm::vec4 vertex;
		glm::vec3 normal;
		glm::vec2 uv;
		PackedVertex(glm::vec4 vertex, glm::vec2 uv, glm::vec3 normal) {
			this->vertex = vertex, this->uv = uv, this->normal = normal;
		}
		bool operator<(const PackedVertex& other) const {
			return memcmp((void*)this, (void*)&other, sizeof(PackedVertex)) > 0;
		}
	};

public:
	static bool LoadObj(const char* filename, std::vector<glm::vec4>& vertices, std::vector<glm::vec2> & uvs, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices);
};