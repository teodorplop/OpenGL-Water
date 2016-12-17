#include "GameManager.h"
#include "../Core/Input.h"
#include "../Core/Mesh.h"
#include "../Core/Texture.h"
#include "../Shaders/Shader.h"

#include "Terrain\Terrain.h"
#include "Terrain\HeightMapGenerator.h"
#include "../Core/Renderer/Light.h"

#include <ctime>

GameManager::GameManager(Camera* camera) : ITickable() {
	srand((unsigned int)time(NULL));
	int seed = rand() % 1000;
	HeightMapGenerator::Generate("Textures/HeightMaps/heightMap", 256, 256, 7, seed);

	cameraController = new CameraController(camera);

	// sky color
	glm::vec3 skyColor = glm::vec3(0.815f, 0.925f, 0.992f);
	glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);

	renderer = new Renderer(camera);

	Shader* shader = new Shader("Shaders/Shader.vert", "Shaders/Shader.frag");
	Mesh* terrainMesh = Terrain::GenerateMesh("Textures/HeightMaps/heightMap.png");
	Texture* grassTexture = new Texture("Textures/grass.png");

	terrain = new Renderable();
	terrain->SetMesh(terrainMesh);
	terrain->SetShader(shader);
	terrain->SetTexture(grassTexture, 10);

	waterRenderer = new WaterRenderer(camera);

	Shader* waterShader = new Shader("Shaders/WaterShader.vert", "Shaders/WaterShader.frag");
	Mesh* waterMesh = Water::GenerateMesh(glm::vec2(Terrain::size, Terrain::size));
	Texture* waterDudv = new Texture("Textures/Water/dudv.png");
	Texture* waterNormal = new Texture("Textures/Water/normal.png");

	water = new Water();
	water->SetMesh(waterMesh);
	water->SetShader(waterShader);
	water->SetDUDV(waterDudv);
	water->SetNormal(waterNormal);
	water->textureTiling = 4;
	water->distorsionStrength = 0.04f;

	renderer->Register(terrain);
	waterRenderer->Register(water);
}

GameManager::~GameManager() {
	delete renderer;
	delete cameraController;
	delete camera;
}

void GameManager::Tick() {
	float value = Input::GetScroll();
	float sign = 0.0f;
	if (value > 0.5f) {
		sign = 1.0f;
	} else if (value < -0.5f) {
		sign = -1.0f;
	}

	if (fabs(sign) > 0.5f) {
		if (Input::GetKey('1')) {
			water->textureTiling += sign * 0.1f;
		} else if (Input::GetKey('2')) {
			water->distorsionStrength += sign * 0.01f;
		}	else if (Input::GetKey('3')) {
			water->moveSpeed += sign * 0.01f;
		} else if (Input::GetKey('4')) {
			water->specularPower += sign * 0.5f;
		} else if (Input::GetKey('5')) {
			Light::color.r = glm::clamp(Light::color.r + sign * 0.01f, 0.0f, 1.0f);
		} else if (Input::GetKey('6')) {
			Light::color.g = glm::clamp(Light::color.g + sign * 0.01f, 0.0f, 1.0f);
		}	else if (Input::GetKey('7')) {
			Light::color.b = glm::clamp(Light::color.b + sign * 0.01f, 0.0f, 1.0f);
		}
	}
}