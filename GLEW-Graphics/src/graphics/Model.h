#pragma once
#include "utils/Common.h"
#include "math/math.h"
#include "graphics/Mesh.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/material.h"

class Model
{
public:
	Model(std::vector<Mesh>& meshs, mat4& transform);
	~Model();

	void LoadFromFile(String path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	const String& determineTextureType(const aiScene* scene, aiMaterial* mat);
private:
	std::vector<Mesh>& m_Meshs;
	mat4& m_Transform;
};