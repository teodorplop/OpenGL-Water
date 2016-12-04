#pragma once

#include <glm\glm.hpp>

#include <vector>
#include "Buffers\Buffer.h"
#include "Buffers\IndexBuffer.h"
#include "Buffers\VertexArray.h"

class Mesh {
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	VertexArray* vArray;
	IndexBuffer* iBuffer;
public:
	Mesh(std::vector<glm::vec4> vertices, std::vector<glm::vec2> uvs, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
	~Mesh();

	VertexArray* GetVertexArray();
	IndexBuffer* GetIndexBuffer();

	static Mesh* LoadFromObj(const char* filename);
};
