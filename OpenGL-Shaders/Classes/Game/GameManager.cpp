#include "GameManager.h"
#include "../Core/Mesh.h"
#include "../Core/Texture.h"
#include "../Shaders/Shader.h"

#include "Terrain\Terrain.h"

GameManager::GameManager(Camera* camera) {
	cameraController = new CameraController(camera);

	// sky color
	glm::vec3 skyColor = glm::vec3(0.815f, 0.925f, 0.992f);
	glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);

	renderer = new Renderer(camera);

	Shader* shader = new Shader("Shaders/Shader.vert", "Shaders/Shader.frag");
	Mesh* terrainMesh = Terrain::GenerateMesh("Textures/HeightMaps/heightMap.png");
	Texture* grassTexture = new Texture("Textures/grass.png");

	Renderable* terrain = new Renderable();
	terrain->SetMesh(terrainMesh);
	terrain->SetShader(shader);
	terrain->SetTexture(grassTexture, 10);

	waterRenderer = new WaterRenderer(camera);

	Shader* waterShader = new Shader("Shaders/WaterShader.vert", "Shaders/WaterShader.frag");
	Mesh* waterMesh = Water::GenerateMesh(glm::vec2(Terrain::size, Terrain::size));
	Texture* waterDudv = new Texture("Textures/Water/dudv.png");
	Texture* waterNormal = new Texture("Textures/Water/normal.png");

	Water* water = new Water();
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
