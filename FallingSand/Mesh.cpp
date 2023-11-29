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

void EnabledAttributePointer(int shaderLocation, int floatComponentCount, size_t offset)
{
	glVertexAttribPointer(shaderLocation, floatComponentCount, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
	glEnableVertexAttribArray(shaderLocation);
}

#define COPY_TO_VERTEX_ARRAY(src, dst) \
if (src) \
{ \
	for (size_t i = 0; i < count; i++) vertices[i].dst = src[i]; \
}

void Mesh::SetVertices(Vec3* positions, Vec2* uvs, int count)
{
	if (vertices) delete[] vertices;

	vertices = new Vertex[count];
	COPY_TO_VERTEX_ARRAY(positions, position)
	COPY_TO_VERTEX_ARRAY(uvs, uv)
	vertexCount = count;

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * count, vertices, GL_STATIC_DRAW);

	EnabledAttributePointer(0, 3, offsetof(Vertex, position));
	EnabledAttributePointer(1, 3, offsetof(Vertex, uv));
}

void Mesh::Draw(const Mat4& objectMatrix)
{
	Shader::SetMatrix("ModelMatrix", objectMatrix);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}
