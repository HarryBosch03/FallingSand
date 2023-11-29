#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = ProjectionMatrix * vec4(vertex, 1.0);
}