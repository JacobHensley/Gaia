#version 330 core

layout (location = 0) out vec4 color;

in vec4 f_Position; //v_
in vec2 f_TexCoord;
in float f_TextureID;
in vec4 f_Color;

uniform sampler2D u_Textures[32];

void main() 
{
	
	vec4 textureColor = vec4(1.0);
	if (f_TextureID > 0.0)
	{
		int tid = int(f_TextureID - 0.5f);	
		textureColor = texture(u_Textures[tid], f_TexCoord);
	}
	
	color = textureColor * f_Color;
}
