#version 330 core

layout (location = 0) out vec4 color;

in vec4 pos;
in vec2 texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() 
{
	vec4 col = pos * 0.5 + 0.5;

	color = texture(u_Texture, texCoord); //u_Color; //vec4(col.r, col.g, col.b, 1);
}