#version 330 core

layout (location = 0) out vec4 color;

in vec4 pos;
in vec2 texCoord;
in float textureID;
in vec4 col;

uniform sampler2D u_Textures[32];

void main() 
{
	
	vec4 textureColor = vec4(1.0);
	if (textureID > 0.0)
	{
		int tid = int(textureID - 0.5f);	
		textureColor = texture(u_Textures[tid], texCoord);
	}
	
	color = textureColor * col;

//	color = col;
}
