#version 330 core

layout (location = 0) in vec4 position;

out vec4 pos;

uniform mat4 u_ModelMatrix;

void main() 
{
	gl_Position = u_ModelMatrix * position;
	pos = position;
}