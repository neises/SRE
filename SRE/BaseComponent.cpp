#include "BaseComponent.h"



namespace SRE
{
	using namespace SRE;

	BaseComponent::BaseComponent() : m_IsEnabled(true)
	{
	}


	BaseComponent::~BaseComponent()
	{
	}

	void BaseComponent::SetTransfrom(Transform* _pTransfrom)
	{
		m_pTransform = _pTransfrom;
	}

	void BaseComponent::Initialize(const Context& _Context, Transform* _pTransform)
	{
		// nothing to do
	}

	void BaseComponent::Update(const Context& _Context, Transform* _pTransform)
	{
		// nothing to do
	}

	void BaseComponent::Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader)
	{
		// nothing to do
	}

}
