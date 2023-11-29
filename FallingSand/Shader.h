#pragma once

#include "Graphics.h"
#include "Math.h"

#include <string>

#define SET_UNIFORM_DEF(funcName, type) \
static void funcName(const std::string& name, type value); \
static void funcName(GLint loc, type value);

class Shader
{
	GLint success;
	
	GLuint vertexShader, fragmentShader, program;
	std::string vertexShaderFilename, fragmentShaderFilename;

	void CompileShader(GLuint shader, const std::string& filepath);

public:

	const inline GLuint Program() const { return program; }

	SET_UNIFORM_DEF(SetMatrix, Mat4)

	SET_UNIFORM_DEF(SetFloat, float)
	SET_UNIFORM_DEF(SetVec2, Vec2)
	SET_UNIFORM_DEF(SetVec3, Vec3)

	SET_UNIFORM_DEF(SetInt, int)
	SET_UNIFORM_DEF(SetIVec2, IVec2)
	SET_UNIFORM_DEF(SetIVec3, IVec3)

	Shader();
	Shader(const Shader& other) = delete;
	Shader& operator=(const Shader& other) = delete;
	~Shader();

	void Load(const std::string& vertexShaderFilepath, const std::string& fragmentShaderPath);
	void Reload();

	void Bind();

	static void DrawStaticGui();
	static void ReloadAllShaders();
};