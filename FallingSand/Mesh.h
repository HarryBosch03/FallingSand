#pragma once

#include "Graphics.h"
#include "Math.h"

#include <string>

struct Vertex
{
	Vec3 position;
	Vec2 uv;
};

class Mesh
{
	GLuint vbo, vao;
	Vertex* vertices;
	int vertexCount;

public:
	Mesh();
	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh& other) = delete;
	~Mesh();

	void SetVertices(Vec3* positions, Vec2* uvs, int count);
	inline void SetVertices(Vec3* positions, int count) { SetVertices(positions, nullptr, count); }
	void Draw(const Mat4& objectMatrix);
};