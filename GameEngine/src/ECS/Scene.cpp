#include "SDL.h"

#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/AnimationSystem.h"
#include "Systems/StateMachineSystem.h"

namespace ProjectAlpha {
Scene::Scene() {
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();
	AddSystem<AnimationSystem>();
	AddSystem<StateMachineSystem>();
	AddSystem<RenderSystem>();
}
Scene::Scene(std::string name) {
	m_name = name;
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();
	AddSystem<AnimationSystem>();
	AddSystem<StateMachineSystem>();
	AddSystem<RenderSystem>();
}

Scene::~Scene() {
	m_entities.clear();
}

Entity Scene::CreateEntity(std::string tag = "Entity") {
	Entity entity = { m_entities.create(), this };
	entity.Add<TagComponent>(tag);
	return entity;
}

void Scene::DestroyEntity(Entity entity) {
	//Check if entity has a parent
	if (entity.Has<ParentComponent>()) {
		auto parent = entity.Get<ParentComponent>();
		//Check if deleted entity's parent keeps track of its children:
		if (parent.Parent.Has<ChildrenComponent>()) {
			//Delete the child from the list of children:
			auto& children = parent.Parent.Get<ChildrenComponent>().Children;
			children.erase(std::remove_if(children.begin(), children.end(),
				[entity](Entity e) { 
					return e == entity; 
				}), 
				children.end());
		}
	}
	if (entity.Has<ChildrenComponent>()) {
		for (auto e : entity.Get<ChildrenComponent>().Children) {
			DestroyEntity(e);
		}
	}
	m_entities.destroy(entity);
}

void Scene::OnEvent(SDL_Event* event) {
	if (!m_paused) {
		for (auto& system : m_systems) {
			system->OnEvent(event);
		}
	}
}

void Scene::OnUpdate() {
	if (!m_paused) {
		for (auto& system : m_systems) {
			system->OnUpdate();
		}

		//Remove Destroy Flagged Entities:
		auto entities = GetEntitiesWith<DestroyFlag>();
		entities.each([this](auto entity, auto& flag) {
			DestroyEntity({ entity, this });
			});
	}
}

//void Scene::OnRender(Renderer& renderer) {
//	RenderSystem->OnUpdate();
//}




void Scene::Cleanup() {
	if (!m_paused) {
		//Do entitiy cleanup here
	}
}





Entity Scene::GetEntity(entt::entity id) { 
	return Entity(id, this); 
}

Entity Scene::GetEntityByName(std::string name) {
	auto entities = GetEntitiesWith<TagComponent>();
	for (auto entity : entities) {
		const auto& tag = entities.get<TagComponent>(entity);
		if (tag.GetTag() == name)
			return Entity{ entity, this };
	}
	return {};
}

} //END namespace ProjectAlpha