#include "Water.h"
#include "WaterRenderer.h"
#include "../../TimeFrame.h"
#include<vector>

Water::Water() {
	transform = new Transform();
	textureTiling = 1;
	moveFactor = 0;
	distorsionStrength = 0.04f;
}

Water::~Water() {
	delete transform;
}

void Water::SetMesh(Mesh* mesh) {
	this->mesh = mesh;
}

void Water::SetShader(Shader* shader) {
	this->shader = shader;
}

void Water::SetDUDV(Texture* texture) {
	this->dudv = texture;
}
void Water::SetNormal(Texture* texture) {
	this->normal = texture;
}

Mesh* Water::GetMesh() {
	return mesh;
}

Shader* Water::GetShader() {
	return shader;
}

Texture* Water::GetDUDV() {
	return dudv;
}

Texture* Water::GetNormal() {
	return normal;
}

float Water::GetMoveFactor() {
	return moveFactor;
}

Transform* Water::GetTransform() {
	return transform;
}

void Water::Tick() {
	moveFactor += TimeFrame::deltaTime / 40.0f;
	moveFactor = fmod(moveFactor, 1.0f);
}

Mesh* Water::GenerateMesh(glm::vec2 size) {
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	for (int i = 0; i < 2; ++i) {
		float x = i * size.x;
		for (int j = 0; j < 2; ++j) {
			float z = j * size.y;

			vertices.push_back(glm::vec4(x, 0, z, 1));
			uvs.push_back(glm::vec2(i, j));
			normals.push_back(glm::vec3(0, 1, 0));
		}
	}
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);

	return new Mesh(vertices, uvs, normals, indices);
}