#include "Model.h"

Model::Model(std::vector<Mesh> meshs, mat4 transform)
	:	m_Meshs(meshs), m_Transform(transform) 
{

}

Model::Model(String filepath)
{
	LoadFromFile(filepath);
}

Model::~Model()
{
}

void Model::LoadFromFile(String path)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	ProcessNode(scene->mRootNode, scene);

}

String textype;

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	std::vector<MeshVertex> vertices;
	std::vector<uint> indices;
	std::vector<MeshTexture> textures;

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

		if (textype.empty()) textype = determineTextureType(scene, mat);
	}

	// Walk through each of the mesh's vertices
	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex vertex;

		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;

		if (mesh->mTextureCoords[0])
		{
			vertex.texcoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.texcoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for(uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (uint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<MeshTexture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", scene);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

void Model::PrintMeshData()
{
	for (uint i = 0; i < m_Meshs.size(); i++)
	{
		Mesh mesh = m_Meshs[i];
		for (uint j = 0; j < mesh.m_Vertices.size(); j++)
		{
			MeshVertex vertex = mesh.m_Vertices[j];
			std::cout << "Vertex:   X: " << vertex.x << " Y: " << vertex.y << " X: " << vertex.z << std::endl;
			std::cout << "TexCoord: X: " << vertex.texcoord.x << " Y: " << vertex.texcoord.y << std::endl;
		}

		for (uint j = 0; j < mesh.m_Indices.size(); j++)
		{
			uint index = mesh.m_Indices[j];
			std::cout << index << std::endl;
		}
	}
}

std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, String typeName, const aiScene* scene) const
{
	std::vector<MeshTexture> textures;
	for (uint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		String texture = str.data;
		std::cout << texture << std::endl;
	}
	return textures;
}


void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshs.push_back(this->ProcessMesh(mesh, scene));
	}

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i], scene);
	}
}

String Model::determineTextureType(const aiScene* scene, aiMaterial* mat)
{
	aiString textypeStr;
	mat->GetTexture(aiTextureType_DIFFUSE, 0, &textypeStr);
	String textypeteststr = textypeStr.C_Str();
	if (textypeteststr == "*0" || textypeteststr == "*1" || textypeteststr == "*2" || textypeteststr == "*3" || textypeteststr == "*4" || textypeteststr == "*5")
	{
		if (scene->mTextures[0]->mHeight == 0)
		{
			return "embedded compressed texture";
		}
		else
		{
			return "embedded non-compressed texture";
		}
	}
	if (textypeteststr.find('.') != String::npos)
	{
		return "textures are on disk";
	}
	return "";
}