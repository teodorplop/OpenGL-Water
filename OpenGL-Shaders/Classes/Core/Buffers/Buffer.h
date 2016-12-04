#pragma once

#include <glm\glm.hpp>

#include <GL/glew.h>
#include <vector>

class Buffer {
private:
	GLuint bufferID;
	GLsizei componentCount;
public:
	Buffer(GLfloat* data, GLsizei count, GLsizei componentCount);
	Buffer(const std::vector<glm::vec2>& data);
	Buffer(const std::vector<glm::vec3>& data);
	Buffer(const std::vector<glm::vec4>& data);
	~Buffer();

	void Bind();
	void Unbind();

	GLsizei GetComponentCount();
};