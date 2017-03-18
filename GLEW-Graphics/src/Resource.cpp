#include "Resource.h"
#include "graphics\Shader.h"
#include "graphics\Texture.h"

Resource::ResourceMap Resource::s_ResourceMap;

Texture* Resource::LoadTexture(const String& name, const String& path)
{
	Texture* texture = new Texture(path);
#if _DEBUG 
	if (s_ResourceMap.find(name) != s_ResourceMap.end()) {
		std::cout << "Warning: overwriting existing resource " << name << "!" << std::endl;
	}
#endif
	s_ResourceMap[name] = { Texture::GetType(), texture };
	return texture;
}

Shader* Resource::LoadShader(const String& name, const String& vertexPath, const String& fragmentPath)
{
	Shader* shader = new Shader(vertexPath, fragmentPath);
#if _DEBUG 
	if (s_ResourceMap.find(name) != s_ResourceMap.end()) {
		std::cout << "Warning: overwriting existing resource " << name << "!" << std::endl;
	}
#endif
	s_ResourceMap[name] = { Shader::GetType(), shader };
	return shader;
}

void* Resource::Get(const String& name)
{
	return s_ResourceMap[name].pointer;
}
