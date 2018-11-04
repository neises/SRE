#include "Scene.h"
#include "Utils.h"
#include "SceneObject.h"
#include "Log.h"

namespace SRE
{
	using namespace SRE;

	Scene::Scene() : m_aSceneObjects(std::vector<SceneObject*>())
	{

	}

	Scene::~Scene()
	{
		for (SceneObject* pChild : m_aSceneObjects)
		{
			SAFE_DELETE(pChild);
		}
	}

	void Scene::AddChild(SceneObject* _pSceneObject)
	{
		if (_pSceneObject)
		{
			m_aSceneObjects.push_back(_pSceneObject);
		}

	}

	void Scene::RemoveChild(SceneObject* _pSceneObject, bool bShouldDeleteObject)
	{
		auto it = find(m_aSceneObjects.begin(), m_aSceneObjects.end(), _pSceneObject);

		if (it == m_aSceneObjects.end())
		{
			Logger::GetLoggerInstance()->L_WARNING("Missing SceneObject");
			return;
		}

		
		if (bShouldDeleteObject)
		{
			m_aSceneObjects.erase(it);
			delete _pSceneObject;
			_pSceneObject = nullptr;
		}
		else
		{
			m_aSceneObjects.erase(it);
		}

	}

	std::vector<SceneObject*>& Scene::GetSceneObjects() 
	{
		return m_aSceneObjects;
	}

}