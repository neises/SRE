#pragma once

#include <vector>
#include <string>

#include "assimp\include\Importer.hpp"
#include "assimp\include\scene.h"
#include "assimp\include\postprocess.h"

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

namespace SRE
{

	class Model
	{
	public:
		Model();

		void LoadModel(const std::string& fileName);
		void RenderModel();
		void ClearModel();

		~Model();

	private:

		void LoadNode(aiNode *_pNode, const aiScene *_pScene);
		void LoadMesh(aiMesh *_pMesh, const aiScene *_pScene);
		void LoadMaterials(const aiScene *_pScene);

		std::vector<Mesh*> m_aMeshList;
		std::vector<Texture*> m_aTexturList;
		std::vector<unsigned int> m_aMeshToTexture;


		//debugging info
		int m_iVerticesCount;
		int m_iIndicesCount;

	};

}