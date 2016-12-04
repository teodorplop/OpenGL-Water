#include "Shader.h"
#include "../Utils/FileIO.h"

GLuint Shader::Compile(GLuint type, const char* source) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLchar infoLog[1024];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", type, infoLog);
	}

	return shader;
}

void Shader::CompileShaders(const char* vertexSource, const char* fragmentSource) {
	vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
	fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar errorLog[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", errorLog);
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	string vertexCode = FileIO::GetFileContents(vertexFile);
	string fragmentCode = FileIO::GetFileContents(fragmentFile);
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	CompileShaders(vertexSource, fragmentSource);
}

Shader::~Shader() {
	glDeleteProgram(shaderProgram);
}

void Shader::Bind() {
	glUseProgram(shaderProgram);
}
void Shader::Unbind() {
	glUseProgram(0);
}

void Shader::SetUniformMatrix4fv(const char* name, const glm::mat4& matrix) {
	GLint matrixID = glGetUniformLocation(shaderProgram, name);
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &matrix[0][0]);
}
void Shader::SetUniform1f(const char* name, const float& value) {
	GLint floatID = glGetUniformLocation(shaderProgram, name);
	glUniform1f(floatID, value);
}
void Shader::SetUniform2f(const char* name, const glm::vec2& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform2f(vectorID, vector.x, vector.y);
}
void Shader::SetUniform3f(const char* name, const glm::vec3& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform3f(vectorID, vector.x, vector.y, vector.z);
}
void Shader::SetUniform4f(const char* name, const glm::vec4& vector) {
	GLint vectorID = glGetUniformLocation(shaderProgram, name);
	glUniform4f(vectorID, vector.x, vector.y, vector.z, vector.w);
}
void Shader::SetUniform1i(const char* name, const int& value) {
	GLint intID = glGetUniformLocation(shaderProgram, name);
	glUniform1i(intID, value);
}