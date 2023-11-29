#include "Graphics.h"

#include "Math.h"
#include "Game.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void Graphics::StartFrame()
{
	float v = 0.1f;
	glClearColor(v, v, v, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::EndFrame()
{
	glfwSwapBuffers(MainWindow());
	glfwPollEvents();
}

void Graphics::ImGuiInitialize()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(MainWindow(), true);
	ImGui_ImplOpenGL3_Init();
}

void Graphics::ImGuiStartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Graphics::ImGuiEndFrame()
{
	ImGui::Render();

	auto data = ImGui::GetDrawData();
	if (data)
	{
		ImGui_ImplOpenGL3_RenderDrawData(data);
	}
}

void Graphics::ImGuiCleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
