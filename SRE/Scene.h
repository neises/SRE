#pragma once
#include <vector>

namespace SRE
{
	class SceneObject;

}
 
namespace SRE
{

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void AddChild(SceneObject* _pSceneObject);
		void RemoveChild(SceneObject* _pSceneObject, bool bShouldDeleteObject = false);

		std::vector<SceneObject*>& GetSceneObjects();

	private:

		std::vector<SceneObject*> m_aSceneObjects;
		bool m_bIsInitialized;
	};
}

