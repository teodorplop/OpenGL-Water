#pragma once

#include<GL/glew.h>
#include <vector>

class IndexBuffer {
private:
	GLuint bufferID;
	GLsizei count;
public:
	IndexBuffer(GLuint* data, GLsizei count);
	IndexBuffer(const std::vector<unsigned int>& data);
	~IndexBuffer();
	void Bind();
	void Unbind();
	GLsizei GetCount();
};