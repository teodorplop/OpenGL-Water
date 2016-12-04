#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(GLuint* data, GLsizei count) : count(count) {
	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	Unbind();
}
IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data) {
	count = data.size();

	glGenBuffers(1, &bufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), &data[0], GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &bufferID);
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void IndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLsizei IndexBuffer::GetCount() {
	return count;
}