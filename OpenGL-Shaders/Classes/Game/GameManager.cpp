#include "GameManager.h"
#include "../Core/Mesh.h"
#include "../Core/Texture.h"
#include "../Shaders/Shader.h"

#include "Terrain\Terrain.h"
#include "Terrain\HeightMapGenerator.h"

void Test(Camera* camera) {
	CameraController* cameraController = new CameraController(camera);

	glm::vec3 skyColor = glm::vec3(0.815f, 0.925f, 0.992f);
	glClearColor(skyColor.x, skyColor.y, skyColor.z, 1.0f);

	Renderer* renderer = new Renderer(camera);

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	vertices.push_back(glm::vec4(-100, -100, 50, 1));
	vertices.push_back(glm::vec4(100, -100, 50, 1));
	vertices.push_back(glm::vec4(100, 100, 50, 1));
	vertices.push_back(glm::vec4(-100, 100, 50, 1));

	uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(1, 0));
	uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(0, 1));

	normals.push_back(glm::vec3(0, 0, 1));
	normals.push_back(glm::vec3(0, 0, 1));
	normals.push_back(glm::vec3(0, 0, 1));
	normals.push_back(glm::vec3(0, 0, 1));

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(2);

	Shader* shader = new Shader("Shaders/MyShader.vert", "Shaders/MyShader.frag", "Shaders/MyShader.geom");
	Mesh* mesh = new Mesh(vertices, uvs, normals, indices);
	Texture* texture = new Texture("Textures/grass.png");

	Renderable* renderable = new Renderable();
	renderable->SetMesh(mesh);
	renderable->SetShader(shader);
	renderable->SetTexture(texture, 1);

	renderer->Register(renderable);
}

GameManager::GameManager(Camera* camera) {
	//Test(camera);
	//return;

	HeightMapGenerator::Generate("Textures/HeightMaps/heightMap", 256, 256, 7, 0);

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
