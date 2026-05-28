#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray() {
	for (int i = 0; i < buffers.size(); ++i) {
		delete buffers[i];
	}
	buffers.clear();
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::AddBuffer(Buffer* buffer, GLuint index) {
	Bind();
	buffer->Bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

	buffer->Unbind();
	Unbind();

	buffers.push_back(buffer);
}

void VertexArray::Bind() {
	glBindVertexArray(arrayID);
}
void VertexArray::Unbind() {
	glBindVertexArray(0);
}