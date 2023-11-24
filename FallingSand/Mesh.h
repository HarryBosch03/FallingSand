#pragma once

#include "Graphics.h"
#include "Math.h"

class Mesh
{
	GLuint vbo, vao;
	Vec3* vertices;
	int vertexCount;

public:
	Mesh();
	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh& other) = delete;
	~Mesh();

	void SetVertices(Vec3* loc, int count);
	void Draw(const Mat4& objectMatrix);
};