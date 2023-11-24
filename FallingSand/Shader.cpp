#include "Shader.h"

#include "Game.h"
#include "Math.h"

#include <iostream>
#include <fstream>

std::string ReadFile(const std::string& filepath);

const int logSize = 512;
char logInfo[logSize];

Shader* currentlyBoundShader = nullptr;

Shader::Shader()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	program = glCreateProgram();

	success = GL_FALSE;
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(program);

	vertexShader = 0;
	fragmentShader = 0;
}

void Shader::Load(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath)
{
	this->vertexShaderFilepath = vertexShaderFilepath;
	this->fragmentShaderFilepath = fragmentShaderFilepath;

	Reload();
}

void Shader::CompileShader(GLuint shader, const std::string& filepath)
{
	std::string file = ReadFile(filepath);
	const char* file_c = file.c_str();

	glShaderSource(shader, 1, &file_c, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(shader, logSize, nullptr, logInfo);
		std::cout << "Failed to Compile \"" << filepath << "\"\n\n" << logInfo << "\n   ---------------   \n";
	}
}

void Shader::Reload()
{
	CompileShader(vertexShader, vertexShaderFilepath);
	CompileShader(fragmentShader, fragmentShaderFilepath);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetProgramInfoLog(program, logSize, nullptr, logInfo);
		std::cout <<
			"Failed to Link Shader \"" <<
			vertexShaderFilepath << "\" and \"" <<
			fragmentShaderFilepath << "\"\n\n" <<
			logInfo << "\n   ---------------   \n";
	}
}

void Shader::Bind()
{
	glUseProgram(program);
	currentlyBoundShader = this;

	int screenWidth, screenHeight;
	glfwGetWindowSize(MainWindow(), &screenWidth, &screenHeight);
	float aspect = (float)screenWidth / screenHeight;
	float camSize = 10.0f;

	Mat4 projection = glm::scale(Mat4(1), { 1.0f / camSize, aspect / camSize, 1.0f });
	Shader::SetMatrix("ProjectionMatrix", projection);
}

#define SHADER_SET_UNIFORM(funcName, type, call) \
void Shader:: ## funcName(const std::string& name, type value) \
{ \
	Shader* shader = currentlyBoundShader; \
	if (!shader) \
	{ \
		std::cout << "Cannot set Uniform, no Shader is Bound\n"; \
		return; \
	} \
	auto loc = glGetUniformLocation(shader->Program(), name.c_str()); \
	call; \
} \
void Shader:: ## funcName(GLint loc, type value) \
{ \
	Shader* shader = currentlyBoundShader; \
	if (!shader) \
	{ \
		std::cout << "Cannot set Uniform, no Shader is Bound\n"; \
		return; \
	} \
	call; \
}

SHADER_SET_UNIFORM(SetMatrix, Mat4, glUniformMatrix4fv(loc, 1, false, (float*)&value))

SHADER_SET_UNIFORM(SetFloat, float, glUniform1fv(loc, 1, &value))
SHADER_SET_UNIFORM(SetVec2, Vec2, glUniform2fv(loc, 1, &value.x))
SHADER_SET_UNIFORM(SetVec3, Vec3, glUniform3fv(loc, 1, &value.x))

SHADER_SET_UNIFORM(SetInt, int, glUniform1iv(loc, 1, &value))
SHADER_SET_UNIFORM(SetIVec2, IVec2, glUniform2iv(loc, 1, &value.x))
SHADER_SET_UNIFORM(SetIVec3, IVec3, glUniform3iv(loc, 1, &value.x))

std::string ReadFile(const std::string& filepath)
{
	std::fstream fs(filepath);

	std::string res, line;
	while (std::getline(fs, line))
	{
		res += line + "\n";
	}

	fs.close();
	return res;
}
