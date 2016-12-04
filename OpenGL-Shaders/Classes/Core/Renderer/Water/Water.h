#pragma once

#include <glm\glm.hpp>

#include "../../Tickable/ITickable.h"
#include "../../../Core/Mesh.h"
#include "../../../Shaders/Shader.h"
#include "../../../Core/Transform.h"
#include "../../Texture.h"

class Water : public ITickable {
private:
	Mesh* mesh;
	Shader* shader;
	Texture* dudv;
	Texture* normal;
	Transform* transform;
	float moveFactor;

public:
	Water();
	~Water();

	float textureTiling;
	float distorsionStrength;

	void SetMesh(Mesh* mesh);
	void SetShader(Shader* shader);
	void SetDUDV(Texture* texture);
	void SetNormal(Texture* normal);

	Mesh* GetMesh();
	Shader* GetShader();
	Texture* GetDUDV();
	Texture* GetNormal();
	Transform* GetTransform();
	float GetMoveFactor();

	void Tick();

	static Mesh* GenerateMesh(glm::vec2 size);
};