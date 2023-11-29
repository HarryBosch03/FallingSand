#include "Game.h"

#include "Graphics.h"
#include "Math.h"
#include "Mesh.h"
#include "Shader.h"

Game* currentGame = nullptr;

void Game::FixedUpdate()
{

}

void Game::Update()
{
	Shader::DrawStaticGui();
}

void Game::Draw()
{
	shader->Bind();
	quad->Draw(Mat4(1));
}

bool Game::Continue()
{
	return !glfwWindowShouldClose(MainWindow());
}

void Game::Run()
{
	Graphics::ImGuiInitialize();

	currentGame = this;

	Vec3 verts[] =
	{
		{ -0.5f, -0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{  0.5f,  0.5f, 0.0f },

		{  0.5f,  0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
	};

	Vec2 uvs[] =
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },

		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
	};

	quad = new Mesh();
	quad->SetVertices(verts, uvs, 6);

	shader = new Shader();
	shader->Load("./assets/shaders/sprite.vert", "./assets/shaders/sprite.frag");

	while (Continue())
	{
		while (fixedTime < time)
		{
			FixedUpdate();
			fixedTime += fixedDeltaTime;
		}

		Graphics::ImGuiStartFrame();

		float lastTime = time;
		time = (float)glfwGetTime();
		deltaTime = time - lastTime;

		Update();

		Graphics::StartFrame();
		Draw();
		Graphics::ImGuiEndFrame();
		Graphics::EndFrame();
	}

	if (currentGame == this) currentGame = nullptr;

	delete quad;
	delete shader;

	Graphics::ImGuiCleanup();
}

Game& Game::Current() { return *currentGame; }
