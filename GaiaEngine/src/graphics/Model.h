#pragma once
#include "utils/Common.h"
#include "math/math.h"
#include "graphics/Mesh.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/material.h"
#include <assimp/Importer.hpp>

class Model
{
public:
	Model(std::vector<Mesh> meshs, mat4 transform);
	Model(String filepath);
	~Model();

	void LoadFromFile(String path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, String typeName, const aiScene* scene) const;
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void PrintMeshData();
	String determineTextureType(const aiScene* scene, aiMaterial* mat);

	void Render();
private:
	std::vector<Mesh> m_Meshs;
	std::vector<RenderMesh> m_RenderMeshs;
	mat4 m_Transform;
};