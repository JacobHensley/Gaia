#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 tc;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;

out vec4 pos;
out vec2 texCoord;
out float textureID;
out vec4 col;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

void main() 
{
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * position;

	pos = position;
	texCoord = tc;
	textureID = tid;
	col = color;
}
