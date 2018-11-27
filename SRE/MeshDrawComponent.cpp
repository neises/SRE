#include "MeshDrawComponent.h"
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Log.h"
#include "Model.h"


namespace SRE
{
	using namespace SRE;

	MeshDrawComponent::MeshDrawComponent( Model* _pModel)
	{
		pModel = _pModel;
	}


	MeshDrawComponent::~MeshDrawComponent()
	{
		delete pMesh;
		delete pModel;
	}


	void MeshDrawComponent::Initialize(const Context& _Context, Transform* _pTransform)
	{

	}

	void SRE::MeshDrawComponent::Update(const Context& _Context, Transform* _pTransform)
	{

	}

	void SRE::MeshDrawComponent::Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader)
	{
		//check shader if null
		if (!_pShader)
		{
			SRE::Logger::GetLoggerInstance()->L_ERROR("Shader is null in MeshComponent!");
			return;
		}

		_pShader->Activate(); //activate shader
		_pShader->SetModel(_pTransform->GetMatrix()); //set transform matrix
		//_pShader->SetMaterial(_pMaterial); // set material 
		//pMesh->RenderMesh(); // render the mesh;
		pModel->RenderModel();
	}
}

