#pragma once
#include "Scene.h"

namespace ProjectAlpha {
class Entity {
public:
	Entity() = default;
	Entity(entt::entity handle, Scene* scene);
	Entity(const Entity& other) = default;
	
	bool IsValid() { 
		if (m_entityHandle != entt::null && m_scene != nullptr)
			return true;
		else
			return false;
	}

	//This will set a Destroy flag and the entitiy and its children will 
	//be destroyed at the end of the update loop.
	void Kill();

	template<typename T, typename... Args>
	T& Add(Args&&... args) {

		//PA_ASSERT(!HasComponent<T>(), "Entity already has component!");
		return m_scene->m_entities.emplace<T>(m_entityHandle, std::forward<Args>(args)...);
	}
	template<typename T>
	void Remove() {

		//PA_ASSERT(!HasComponent<T>(), "Component already does not exist!");
		m_scene->m_entities.remove<T>(m_entityHandle);
	}

	template<typename T>
	T& Get() {

		//PA_ASSERT(!HasComponent<T>(), "Entity does not have this Component!");
		return m_scene->m_entities.get<T>(m_entityHandle);
	}

	template<typename T>
	bool Has() {
		//if (m_scene->m_entities.owned<T>())
		//	return m_scene->m_entities.all_of<T>(m_entityHandle);
		//else
		//	return false;
		//return m_scene->m_entities.any_of<T>(m_entityHandle);

		return m_scene->m_entities.all_of<T>(m_entityHandle);

		//return false;
	}

	operator bool() const { return static_cast<uint32_t>(m_entityHandle) != 0; }
	operator entt::entity() const { return m_entityHandle; }
private:
	entt::entity m_entityHandle{ entt::null };
	Scene* m_scene = nullptr;
};

}//END namespace ProjectAlpha