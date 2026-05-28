#include "MasterRenderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera* MasterRenderer::camera = NULL;
WaterFrameBuffer* MasterRenderer::waterFrameBuffer = NULL;
std::set<Renderer*> MasterRenderer::renderers;
std::set<WaterRenderer*> MasterRenderer::waterRenderers;

void MasterRenderer::Initialize(Camera* camera) {
	MasterRenderer::camera = camera;
	waterFrameBuffer = new WaterFrameBuffer();
}
void MasterRenderer::Register(Renderer* renderer) {
	renderers.insert(renderer);
}
void MasterRenderer::Unregister(Renderer* renderer) {
	renderers.erase(renderer);
}
void MasterRenderer::Register(WaterRenderer* renderer) {
	waterRenderers.insert(renderer);
}
void MasterRenderer::Unregister(WaterRenderer* renderer) {
	waterRenderers.erase(renderer);
}

void MasterRenderer::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 cameraPosition = camera->GetPosition();
	float pitch = camera->GetPitch();

	// Move camera underneath
	cameraPosition.y *= -1;
	pitch *= -1;
	camera->SetPosition(cameraPosition);
	camera->SetPitch(pitch);
	
	// Render the scene in the reflection buffer
	waterFrameBuffer->BindReflectionBuffer();
	waterFrameBuffer->Clear();
	for (Renderer* renderer : renderers) {
		renderer->EnableClipPlane(glm::vec4(0, 1, 0, 0));
		renderer->Render();
		renderer->DisableClipPlane();
	}
	waterFrameBuffer->UnbindBuffer();

	// Move camera back
	cameraPosition.y *= -1;
	pitch *= -1;
	camera->SetPosition(cameraPosition);
	camera->SetPitch(pitch);

	// Render the scene in the refraction buffer
	waterFrameBuffer->BindRefractionBuffer();
	waterFrameBuffer->Clear();
	for (Renderer* renderer : renderers) {
		renderer->EnableClipPlane(glm::vec4(0, -1, 0, 0));
		renderer->Render();
		renderer->DisableClipPlane();
	}
	waterFrameBuffer->UnbindBuffer();
	
	// Draw the scene normally
	for (Renderer* renderer : renderers) {
		renderer->Render();
	}

	for (WaterRenderer* renderer : waterRenderers) {
		renderer->Render(waterFrameBuffer);
	}
}
