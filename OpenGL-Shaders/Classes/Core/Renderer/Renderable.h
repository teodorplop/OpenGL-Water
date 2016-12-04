#pragma once

#include "../Mesh.h"
#include "../../Shaders/Shader.h"
#include "../Transform.h"
#include "../Texture.h"

class Renderable {
private:
	Mesh* mesh;
	Shader* shader;
	Transform* transform;
	Texture* texture;
	float textureTiling;

public:
	Renderable();
	~Renderable();

	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	void SetTexture(Texture* texture, float tiling);

	Mesh* GetMesh();
	Shader* GetShader();
	Texture* GetTexture();
	float GetTextureTiling();
	Transform* GetTransform();
};
