#include <iostream>
#include "Graphics.h"
#include "Game.h"
#include "Logging.h"

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

static void GlfwErrorCallback(int error, const char* description);

void Init()
{
	const int defaultWindowWidth = 1280;
	const int defaultWindowHeight = 720;

	glfwSetErrorCallback(GlfwErrorCallback);

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

static void GlfwErrorCallback(int error, const char* description)
{
	Log("GLFW Error [" << error << "] " << description);
}