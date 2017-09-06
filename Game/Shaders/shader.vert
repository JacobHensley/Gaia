#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textCoord;
layout (location = 2) in float textureID;
layout (location = 3) in vec4 color;

out vec4 f_Position;
out vec2 f_TexCoord;
out float f_TextureID;
out vec4 f_Color;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjMatrix;

void main() 
{
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * position;

	f_Position = position;
	f_TexCoord = textCoord;
	f_TextureID = textureID;
	f_Color = color;
}
