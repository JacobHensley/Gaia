#Shader Vertex

#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec4 f_Position;
out vec3 f_Normal;
out vec2 f_TexCoord;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;

	f_Position = position;
	f_Normal = normal;
	f_TexCoord = texCoord;
}

#Shader Fragment

#version 330 core

layout(location = 0) out vec4 color;

in vec4 f_Position;
in vec3 f_Normal;
in vec2 f_TexCoord;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;

void main()
{
	float ambient = 0.1;
	vec3 lightPos = u_LightPos;
	vec3 lightColor = u_LightColor;
	vec3 objectColor = u_ObjectColor;

	vec3 norm = normalize(f_Normal);
	vec3 lightDir = normalize(lightPos - f_Position.xyz);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	vec3 result = (ambient + diffuse) * objectColor;

	color = vec4(result, 1.0);
}