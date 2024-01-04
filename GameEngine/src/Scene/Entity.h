#pragma once


#include "Scene.h"

#include "../Assert.h"


namespace ProjectAlpha {

class Entity {
public:
	Entity() = default;
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;

	template<typename T, typename... Args>
	T& Add(Args&&... args) {

		PA_ASSERT(!HasComponent<T>(), "Entity already has component!");
		return m_scene->m_entities.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
	}
	template<typename T>
	void Remove() {

		PA_ASSERT(!HasComponent<T>(), "Component already does not exist!");
		m_scene->m_entities.remove<T>(m_entityHandle);
	}

	template<typename T>
	T& Get() {

		PA_ASSERT(!HasComponent<T>(), "Entity does not have this Component!");
		return m_scene->m_entities.get<T>(m_entityHandle);
	}

	template<typename T>
	bool Has() {

		return m_scene.lock()->m_entities.has<T>(m_entityHandle);
	}

	operator bool() const { return static_cast<uint32_t>(m_entityHandle) != 0; }
private:
	entt::entity m_entityHandle{ entt::null };
	Scene* m_scene = nullptr;
};

}//END namespace ProjectAlpha