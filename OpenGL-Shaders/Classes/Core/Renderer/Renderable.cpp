#include "Renderable.h"
#include "MasterRenderer.h"

Renderable::Renderable() {
	transform = new Transform();
	textureTiling = 1;
}

Renderable::~Renderable() {
	delete transform;
}

void Renderable::SetMesh(Mesh* mesh) {
	this->mesh = mesh;
}
void Renderable::SetShader(Shader* shader) {
	this->shader = shader;
}
void Renderable::SetTexture(Texture* texture, float tiling) {
	this->texture = texture;
	this->textureTiling = tiling;
}

Mesh* Renderable::GetMesh() {
	return mesh;
}
Shader* Renderable::GetShader() {
	return shader;
}
Texture* Renderable::GetTexture() {
	return texture;
}
float Renderable::GetTextureTiling() {
	return textureTiling;
}
Transform* Renderable::GetTransform() {
	return transform;
}