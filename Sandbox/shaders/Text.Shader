#Shader Vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float textureID;
layout(location = 3) in vec4 color;

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

#Shader Fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 f_Position;
in vec2 f_TexCoord;
in float f_TextureID;
in vec4 f_Color;

uniform sampler2D u_Textures[32];

void main()
{

	vec2 tc = f_TexCoord;
	vec4 textureColor = vec4(1.0);
	if (f_TextureID > 0.0)
	{
		int tid = int(f_TextureID - 0.5f);
		textureColor = texture(u_Textures[tid], tc);
	}

	color = vec4(f_Color.r, f_Color.g, f_Color.b, textureColor.r);
}