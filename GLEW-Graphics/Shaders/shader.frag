#version 330 core

layout (location = 0) out vec4 color;

in vec4 pos;

uniform vec4 u_Color;

void main() 
{
	vec4 col = pos * 0.5 + 0.5;

	color = u_Color; //vec4(col.r, col.g, col.b, 1);
}