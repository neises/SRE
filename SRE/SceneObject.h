#pragma once
#include <vector>
#include "Utils.h"
#include "Shader.h"
#include "ShaderProgram.h"

namespace SRE
{
	class Transform;
	class BaseComponent;
	class Scene;
}
namespace SRE
{

	class SceneObject
	{
	public:
		SceneObject();
		virtual ~SceneObject();

		void AddChild(SceneObject* _pSceneObject);
		void RemoveChild(SceneObject* _pSceneObject);
		void AddComponent(BaseComponent* _pComp);
		void RemoveComponent(BaseComponent* _pComp);

		void SetTransform(Transform *_pTransform);
		Transform* GetTransform() const { return m_pTransform; }

		Scene* GetScene();
		SceneObject* GetParent() const { return m_pParentObject; }


	//protected:
		virtual void Initialize(const Context& _Context);
		virtual void Render(const Context& _Context, ShaderProgram *_pShader);
		virtual void Update(const Context& _Context);

	private:

		std::vector<SceneObject*> m_pChildren;
		std::vector<BaseComponent*> m_pComponents;

		bool m_IsInitialized, m_IsActive;
		Scene* m_pParentScene;
		SceneObject* m_pParentObject;
		Transform* m_pTransform;

		std::vector<SceneObject*> m_pChildrenRuntime;
		std::vector<SceneObject*> m_pChildrenRemoveRuntime;


		// -------------------------
		// Disabling default copy constructor and default 
		// assignment operator.
		// -------------------------
		SceneObject(const SceneObject &_pSceneObject);
		SceneObject& operator=(const SceneObject& _pSceneObject);

	};
}
