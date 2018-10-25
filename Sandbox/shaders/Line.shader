#Shader Vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

out vec4 f_Position;
out vec4 f_Color;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;

	f_Position = position;
	f_Color = color;
}

#Shader Fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 f_Position;
in vec4 f_Color;

void main()
{
	color = vec4(f_Color.r, f_Color.g, f_Color.b, 1.0f);
}