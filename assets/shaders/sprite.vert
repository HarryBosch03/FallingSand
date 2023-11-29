#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;

uniform mat4 ProjectionMatrix;

out vec2 uv0;

void main()
{
    gl_Position = ProjectionMatrix * vec4(vertex, 1.0);
    uv0 = uv;
}