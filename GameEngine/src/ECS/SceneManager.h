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

	/*this used a raw pointer and isnt safe*/
	void AddScene(Scene* scene) {
		m_loadedScenes[scene->GetName()] = std::shared_ptr<Scene>(scene);
	}

	void AddScene(std::shared_ptr<Scene> scene) {
		//m_loadedScenes[scene->GetName()] = scene;
		m_loadedScenes[scene->GetName()] = std::move(scene);
	}

	void RemoveScene(std::string sceneID) {
		m_loadedScenes[sceneID].reset();
	}

	std::shared_ptr<Scene> CreateScene(std::string name) {
		m_loadedScenes[name] = std::make_shared<Scene>(Scene(name));
		return m_loadedScenes[name];
	}
	
private:
	std::shared_ptr<Scene> m_currentScene;
	std::map<std::string, std::shared_ptr<Scene>> m_loadedScenes;
};

} //END namespace ProjectAlpha