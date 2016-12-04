#pragma once

#include <GL/glew.h>
#include <vector>
#include "Buffer.h"

class VertexArray {
private:
	GLuint arrayID;
	std::vector<Buffer*> buffers;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(Buffer* buffer, GLuint index);
	void Bind();
	void Unbind();
};