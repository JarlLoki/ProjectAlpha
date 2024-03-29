#pragma once
#include "SDL.h"
#include "entt/entt.hpp"
#include "System.h"
#include "../Graphics/BasicDataContainers/Rect.h"

namespace ProjectAlpha {

class Entity;
class Renderer;

class Scene {
public:
	Scene();
	Scene(std::string name);

	std::string GetName() { return m_name; }

	Entity CreateEntity(std::string tag);

	void OnEvent(SDL_Event* event);
	void OnUpdate();
	void OnRender(Renderer& renderer);
	
	template <typename T>
	void AddSystem();

	inline entt::registry& GetRegistry() { return m_entities; }
	Entity GetEntity(entt::entity id);

protected:
	std::string m_name;
	entt::registry m_entities;
	std::vector<std::unique_ptr<System>> m_systems;

	friend class Entity;
};


//Add System
template <typename T>
inline void Scene::AddSystem() {
	std::unique_ptr<System> system = std::make_unique<T>();
	system->m_scene = this;
	m_systems.push_back(std::move(system));
}



} //END namespace ProjectAlpha