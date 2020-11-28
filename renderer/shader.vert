#version 330 core

in vec3 Position;
uniform mat4 ViewMatrix, ProjMatrix;

void main()
{
    gl_Position = ProjMatrix * ViewMatrix * vec4(Position, 1.0);
}
