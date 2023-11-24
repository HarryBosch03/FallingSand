#include "Mesh.h"

#include "Shader.h"

Mesh::Mesh()
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	vertices = nullptr;
	vertexCount = 0;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
	delete[] vertices;
}

void Mesh::SetVertices(Vec3* loc, int count)
{
	if (vertices) delete[] vertices;

	vertices = new Vec3[count];
	for (size_t i = 0; i < count; i++)
	{
		vertices[i] = loc[i];
	}
	vertexCount = count;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * count, loc, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
}

void Mesh::Draw(const Mat4& objectMatrix)
{
	Shader::SetMatrix("ModelMatrix", objectMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
