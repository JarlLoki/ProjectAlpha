#pragma once
#include "entt/entt.hpp"
#include "System.h"

namespace ProjectAlpha {

class Entity;
class Renderer;

class Scene {
public:
	Scene();
	~Scene() = default;

	Entity CreateEntity(std::string tag);

	void OnUpdate();
	void OnRender(Renderer& renderer);
	
	template <typename T>
	void AddSystem();

	inline entt::registry& GetEntities() { return m_entities; }

private:
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