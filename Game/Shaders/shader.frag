#version 330 core

layout (location = 0) out vec4 color;

in vec4 pos;
in vec2 texCoord;
in float textureID;
in vec4 col;

uniform sampler2D u_Textures[32];

void main() 
{
//	int tid = int(textureID - 0.5f);	
//	color = texture(u_Textures[tid], texCoord);

	color = col;
}
