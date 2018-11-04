#include "Model.h"
#include "Log.h"

namespace SRE
{
	Model::Model()
	{
		m_iIndicesCount = 0;
		m_iVerticesCount = 0;
	}

	void Model::RenderModel()
	{
		for (size_t i = 0; i < m_aMeshList.size(); i++)
		{
			unsigned int materialIndex = m_aMeshToTexture[i];

			if (materialIndex < m_aTexturList.size() && m_aTexturList[materialIndex])
			{
				m_aTexturList[materialIndex]->UseTexture();
			}

			m_aMeshList[i]->RenderMesh();
		}
	}

	void Model::LoadModel(const std::string & fileName)
	{
		Assimp::Importer importer;
		const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals );

		if (!scene)
		{
			printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
			return;
		}

		LoadNode(scene->mRootNode, scene);

		LoadMaterials(scene);

		SRE::Logger::GetLoggerInstance()->m_pConsole->info("Model-Info: Verices: {0} ,  Indices: {1}",m_iVerticesCount, m_iIndicesCount);
	}

	void Model::LoadNode(aiNode *_pNode, const aiScene * _pScene)
	{
		for (size_t i = 0; i < _pNode->mNumMeshes; i++)
		{
			LoadMesh(_pScene->mMeshes[_pNode->mMeshes[i]], _pScene);
		}

		for (size_t i = 0; i < _pNode->mNumChildren; i++)
		{
			LoadNode(_pNode->mChildren[i], _pScene);
		}

	}

	void Model::LoadMesh(aiMesh *_pMesh, const aiScene *_pScene)
	{
		std::vector<GLfloat> vertices;
		std::vector<unsigned int> indices;
		
		m_iIndicesCount += _pMesh->mNumFaces;
		m_iVerticesCount += _pMesh->mNumVertices;


		for (size_t i = 0; i < _pMesh->mNumVertices; i++)
		{
			vertices.insert(vertices.end(), { _pMesh->mVertices[i].x, _pMesh->mVertices[i].y, _pMesh->mVertices[i].z });
			if (_pMesh->mTextureCoords[0])
			{
				vertices.insert(vertices.end(), { _pMesh->mTextureCoords[0][i].x, _pMesh->mTextureCoords[0][i].y });
			}
			else 
			{
				vertices.insert(vertices.end(), { 0.0f, 0.0f });
			}
			
			vertices.insert(vertices.end(), { -_pMesh->mNormals[i].x, -_pMesh->mNormals[i].y, -_pMesh->mNormals[i].z });
		

			
		}

		for (size_t i = 0; i < _pMesh->mNumFaces; i++)
		{
			aiFace face = _pMesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		Mesh* newMesh = new Mesh();
		newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
		m_aMeshList.push_back(newMesh);
		m_aMeshToTexture.push_back(_pMesh->mMaterialIndex);
	}

	void Model::LoadMaterials(const aiScene *_pScene)
	{
		m_aTexturList.resize(_pScene->mNumMaterials);

		for (size_t i = 0; i < _pScene->mNumMaterials; i++)
		{
			aiMaterial* material = _pScene->mMaterials[i];

			m_aTexturList[i] = nullptr;

			if (material->GetTextureCount(aiTextureType_DIFFUSE))
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					int idx = std::string(path.data).rfind("\\");
					std::string filename = std::string(path.data).substr(idx + 1);

					std::string texPath = std::string("assets/Textures/") + filename;

					m_aTexturList[i] = new Texture(texPath.c_str());

					if (!m_aTexturList[i]->LoadTexture())
					{
						printf("Failed to load texture at: %s\n", texPath);
						delete m_aTexturList[i];
						m_aTexturList[i] = nullptr;
					}
				}
			}

			if (!m_aTexturList[i])
			{
				m_aTexturList[i] = new Texture("assets/Textures/MissingTexture.png");
				m_aTexturList[i]->LoadTextureA();
			}
		}
	}

	void Model::ClearModel()
	{
		for (size_t i = 0; i < m_aMeshList.size(); i++)
		{
			if (m_aMeshList[i])
			{
				delete m_aMeshList[i];
				m_aMeshList[i] = nullptr;
			}
		}

		for (size_t i = 0; i < m_aTexturList.size(); i++)
		{
			if (m_aTexturList[i])
			{
				delete m_aTexturList[i];
				m_aTexturList[i] = nullptr;
			}
		}
	}

	Model::~Model()
	{
	}

}