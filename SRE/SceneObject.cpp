#include "SceneObject.h"
#include "Transform.h"
#include "Utils.h"
#include "Log.h"
#include "BaseComponent.h"


namespace SRE
{
	using namespace SRE;

	SceneObject::SceneObject() :m_pChildren(std::vector<SceneObject*>()),
								m_pComponents(std::vector<BaseComponent*>()),
								m_IsInitialized(false),
								m_IsActive(true),
								m_pParentScene(nullptr),
								m_pParentObject(nullptr),
								m_pTransform(nullptr)
	{

		m_pTransform = new Transform();
		//AddComponent(m_pTransform);
	}

		SceneObject::~SceneObject()
	{
			//Component Cleanup
			for (BaseComponent* pComp : m_pComponents)
			{
				SAFE_DELETE(pComp);
			}

			//Object Cleanup
			for (SceneObject* pChild : m_pChildren)
			{
				SAFE_DELETE(pChild);
			}
	}

		void SceneObject::AddChild(SceneObject* _pSceneObject)
		{
			m_pChildren.push_back(_pSceneObject);
		}

		void SceneObject::SetTransform(Transform *_pTransform)
		{
			m_pTransform = _pTransform;
		}

		void SceneObject::Render(const Context& _Context, ShaderProgram *_pShader)
		{
			for (BaseComponent* pComp : m_pComponents)
			{
				pComp->Render(_Context, m_pTransform, _pShader);
			}

			//children objects draw
			for (SceneObject* pChild : m_pChildren)
			{
				pChild->Render(_Context, _pShader);
			}
		}

		void SceneObject::Update(const Context& _Context)
		{
			//Component Update
			for (BaseComponent* pComp : m_pComponents)
			{
				pComp->Update(_Context, m_pTransform);
			}

			//children objects update
			for (SceneObject* pChild : m_pChildren)
			{
				pChild->Update(_Context);
			}
		}

		void SceneObject::Initialize(const Context& _Context)
	{
			if (m_IsInitialized)
				return;

			//User-Object Initialization
			//Initialize(gameContext);


			//Root-Component Initialization
			for (BaseComponent* pComp : m_pComponents)
			{
				pComp->Initialize(_Context, m_pTransform);
			}

			//Root-Object Initialization
			for (SceneObject* pChild : m_pChildren)
			{
				pChild->Initialize(_Context);
			}

			m_IsInitialized = true;
	}


	void SceneObject::RemoveChild(SceneObject* _pSceneObject)
	{

	}

	void SceneObject::AddComponent(BaseComponent* _pBaseComponent)
	{
		m_pComponents.push_back(_pBaseComponent);
	}

	void SceneObject::RemoveComponent(BaseComponent* _pBaseComponent)
	{

	}

	Scene* SceneObject::GetScene()
	{
		return nullptr;
	}
}