#pragma once
#include "BaseComponent.h"
#include "Utils.h"

namespace SRE
{
	class Transform;
	class Mesh;
	class Material;
	class Shader;
	class ShaderProgram;
	class Model;
}


namespace SRE
{

	class MeshDrawComponent : public SRE::BaseComponent
	{
	public:
		MeshDrawComponent(Model* _pModel);
		~MeshDrawComponent();

	protected:
		virtual void Initialize(const Context& _Context, Transform* _pTransform) override;
		virtual void Update(const Context& _Context, Transform* _pTransform) override;
		virtual void Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader) override;


	private:
		Mesh* pMesh;
		Shader* pShader;
		Model* pModel;
	};
}

