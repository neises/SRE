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
		//BaseComponent::Render(_Context, _pTransform, _pShader);

		//check shader if null
		if (!_pShader)
		{
			SRE::Logger::GetLoggerInstance()->L_ERROR("Shader is null in MeshComponent!");
			return;
		}
		
		_pShader->Activate(); //activate shader

		//set the shader properties via the context info
		_pShader->SetProjection(_Context.m_Projection);
		_pShader->SetView(_Context.m_View);
		_pShader->SetUniform("viewPos", _Context.m_ViewPos);
		_pShader->SetUniform("lightPos", _Context.m_LightPos);
		_pShader->SetUniform("lightColor", _Context.m_LightColor);
		_pShader->SetModel(_pTransform->GetMatrix()); //set transform matrix
		//_pShader->SetMaterial(_pMaterial); // set material 

		// render the model
		pModel->RenderModel();
	}
}

