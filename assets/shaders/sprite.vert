#version 330 core

layout (location = 0) in vec3 positionOS;

uniform mat4 ProjectionMatrix;

void main()
{
    gl_Position = ProjectionMatrix * vec4(positionOS.xyz, 1.0);
}