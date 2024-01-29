#pragma once
#include "Scene.h"

#include <map>
#include <memory>

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
	
	template<typename T>
	void LoadScene() {
		std::shared_ptr<Scene> scene((static_cast<Scene*>(new T)));
		m_loadedScenes[scene.GetName()] = scene;
	}
private:
	std::shared_ptr<Scene> m_currentScene;
	std::map<std::string, std::shared_ptr<Scene>> m_loadedScenes;
};

} //END namespace ProjectAlpha