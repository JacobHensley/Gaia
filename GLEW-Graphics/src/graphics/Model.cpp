#include "Model.h"

Model::Model(std::vector<Mesh>& meshs, mat4& transform)
	:	m_Meshs(meshs), m_Transform(transform) 
{

}

Model::~Model()
{
}

void Model::LoadFromFile(String path)
{
	const aiScene* scene = aiImportFile(path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	processNode(scene->mRootNode, scene);

	aiReleaseImport(scene);
}

String textype;

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
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

std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName, const aiScene * scene)
{
	std::vector<MeshTexture> textures;
	for (unt i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (uint j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.c_str(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // If texture hasn't been loaded already, load it
			MeshTexture texture;
			if (textype == "embedded compressed texture")
			{
				int textureindex = getTextureIndex(&str);
				texture.texture = getTextureFromModel(scene, textureindex);
			}
			else
			{
				string filename = string(str.C_Str());
				filename = directory + '/' + filename;
				wstring filenamews = wstring(filename.begin(), filename.end());
				hr = CreateWICTextureFromFile(dev, devcon, filenamews.c_str(), nullptr, &texture.texture);
			}
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			this->textures_loaded.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}


void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshs.push_back(this->processMesh(mesh, scene));
	}

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}

const String& Model::determineTextureType(const aiScene* scene, aiMaterial* mat)
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
}