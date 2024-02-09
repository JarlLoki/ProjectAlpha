#pragma once
#include <map>
#include <memory>

#include "ECS/Scene.h"

namespace ProjectAlpha {

class SceneManager {
public:
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	std::shared_ptr<Scene> GetCurrentScene() { return m_currentScene; }

	void SetCurrentScene(std::string sceneID) {
		m_currentScene = m_loadedScenes[sceneID];
	}
	
	template<typename T, typename... TArgs>
	void LoadScene(TArgs&&... mArgs) {
		std::shared_ptr<Scene> scene((static_cast<Scene*>(new 
			T(std::forward<TArgs>(mArgs)...))));
		m_loadedScenes[scene->GetName()] = scene;
	}
private:
	std::shared_ptr<Scene> m_currentScene;
	std::map<std::string, std::shared_ptr<Scene>> m_loadedScenes;
};

} //END namespace ProjectAlpha