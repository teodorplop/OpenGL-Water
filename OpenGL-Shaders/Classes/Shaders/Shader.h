#pragma once

#include <glm\glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>

class Shader {
private:
	GLuint vertexShader, fragmentShader, shaderProgram;
	void CompileShaders(const char* vertexSource, const char* fragmentSource);
	GLuint Compile(GLuint type, const char* source);

public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void Bind();
	void Unbind();
	void SetUniformMatrix4fv(const char* name, const glm::mat4& matrix);
	void SetUniform1f(const char* name, const float& value);
	void SetUniform2f(const char* name, const glm::vec2& vector);
	void SetUniform3f(const char* name, const glm::vec3& vector);
	void SetUniform4f(const char* name, const glm::vec4& vector);
	void SetUniform1i(const char* name, const int& value);
};