#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in float textureID;
layout (location = 3) in vec4 color;

out vec4 f_Position;
out vec2 f_TexCoord;
out float f_TextureID;
out vec4 f_Color;

uniform mat4 u_MVP;

void main() 
{
	gl_Position = u_MVP * position;

	f_Position = position;
	f_TexCoord = texCoord;
	f_TextureID = textureID;
	f_Color = color;
}
