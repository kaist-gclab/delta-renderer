#version 330 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
uniform mat4 ViewMatrix, ProjMatrix;

out vec3 FragPos;
out vec3 Normal;

void main()
{
    gl_Position = ProjMatrix * ViewMatrix * vec4(VertexPosition, 1.0);
    FragPos = VertexPosition;
    Normal = VertexNormal;
}
