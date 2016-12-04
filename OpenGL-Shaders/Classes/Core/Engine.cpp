#include "Engine.h"
#include "Window.h"
#include "TimeFrame.h"
#include "Input.h"

#include "Tickable/TickEngine.h"
#include "Renderer/MasterRenderer.h"

#include "../Game/GameManager.h"

#include <cstdio>

Engine::Engine(int argc, char** argv) {
	glutInit(&argc, argv);

	Window* window = new Window("OpenGL Shaders", 1024, 768);
	Input::HandleInput(window);

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Failed to initialize glew: %s\n", glewGetErrorString(error));
	}
	
	Camera* camera = new Camera(Projection::Perspective, 45, (float)window->GetWidth() / window->GetHeight());
	MasterRenderer::Initialize(camera);
	GameManager* gameManager = new GameManager(camera);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	while (!window->Closed()) {
		TimeFrame::Update((float)glfwGetTime());
		TickEngine::Tick();
		
		MasterRenderer::Render();

		Input::Clear();
		window->Update();
	}
}

Engine::~Engine() {
	glfwTerminate();
}