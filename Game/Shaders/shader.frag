#version 330 core

layout (location = 0) out vec4 color;

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
	//	tc.y = 1.0 - tc.y;
		textureColor = texture(u_Textures[tid], tc);
	}
	
	color = vec4(1, 1, 1, textureColor.r); //textureColor * f_Color;
}
