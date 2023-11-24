#include <iostream>
#include "Graphics.h"
#include "Game.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

void Init();
void Loop();
void Cleanup();

GLFWwindow* mainWindow;
GLFWwindow* MainWindow() { return mainWindow; }

int main(int argc, char* argv[])
{
	Init();

	Game game = {};
	game.Run();

	Cleanup();

	return 0;
}

void Init()
{
	const int defaultWindowWidth = 1280;
	const int defaultWindowHeight = 720;

	glfwInit();

	mainWindow = glfwCreateWindow
	(
		defaultWindowWidth,
		defaultWindowHeight,
		"Harry Bosch Presents - Falling Sand",
		nullptr, nullptr
	);

	if (!mainWindow)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(mainWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	glViewport(0, 0, defaultWindowWidth, defaultWindowHeight);
	glfwSetFramebufferSizeCallback(mainWindow, FramebufferSizeCallback);
}

void Cleanup()
{
	glfwTerminate();
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
