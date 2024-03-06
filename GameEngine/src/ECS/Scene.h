#pragma once
#include "entt/entt.hpp"
#include "System.h"


namespace ProjectAlpha {
class Entity;
class Renderer;

class Scene {
public:
	Scene();
	Scene(std::string name);
	Scene(const Scene&) {}
	~Scene();

	std::string GetName() { return m_name; }

	Entity CreateEntity(std::string tag);
	void DestroyEntity(Entity entity); 

	void OnEvent(SDL_Event* event);
	void OnUpdate();
	//void OnRender(Renderer& renderer);
	void Cleanup();
	
	template <typename T>
	void AddSystem();

	inline entt::registry& GetRegistry() { return m_entities; }
	Entity GetEntity(entt::entity id);
	Entity GetEntityByName(std::string name);

	template<typename... Components>
	auto GetEntitiesWith();

	void TogglePause() { m_paused = !m_paused; }
	void Pause() { m_paused = true; }
	void Resume() { m_paused = false; }

	void ToggleHide() { m_hide = !m_hide; }
	void Hide() { m_hide = true; }
	void Show() { m_hide = false; }


protected:
	std::string m_name;
	entt::registry m_entities;
	std::vector<std::unique_ptr<System>> m_systems;
	std::unique_ptr<System> m_renderSystem;

	bool m_paused = false;
	bool m_hide = false;

	friend class Entity;
};


//Add System
template <typename T>
 void Scene::AddSystem() {
	std::unique_ptr<System> system = std::make_unique<T>();
	system->m_scene = this;
	m_systems.push_back(std::move(system));
}

template<typename ... Components>
 auto Scene::GetEntitiesWith() {
	return m_entities.view<Components...>();
}



} //END namespace ProjectAlpha