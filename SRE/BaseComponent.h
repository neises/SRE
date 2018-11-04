#pragma once
#include "Utils.h"


namespace SRE 
{
	class SceneObject;
	class Transform;
	class Shader;
	class ShaderProgram;
}


namespace SRE
{

	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent();

		SceneObject* GetSceneObject() const;
		Transform* GetTransform() const;

		void SetTransfrom(Transform* _pTransfrom);


		virtual void Initialize(const Context& _Context, Transform* _pTransform);
		virtual void Update(const Context& _Context, Transform* _pTransform);
		virtual void Render(const Context& _Context, Transform* _pTransform, ShaderProgram* _pShader);

	private:

		bool m_IsEnabled;
		Transform* m_pTransform;


	};
}

