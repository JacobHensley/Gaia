#Shader Vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec4 f_Position;
out vec2 f_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;

	f_Position = position;
	f_TexCoord = texCoord;
}

#Shader Fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 f_Position;
in vec2 f_TexCoord;

void main()
{
	color = vec4(f_Position.xyz * 10.0, 1.0);
}