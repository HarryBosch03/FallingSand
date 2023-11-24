#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

GLFWwindow* MainWindow();

namespace Graphics
{
	void StartFrame();
	void EndFrame();
	
	void ImGuiInitialize();
	void ImGuiStartFrame();
	void ImGuiEndFrame();
	void ImGuiCleanup();
}