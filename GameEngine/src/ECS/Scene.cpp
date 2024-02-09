#include "SDL.h"

#include "Scene.h"
#include "Entity.h"
#include "Components/Components.h"
#include "Systems/RenderSystem.h"
#include "Systems/ScriptSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/AnimationSystem.h"

namespace ProjectAlpha {
Scene::Scene() {
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();
	AddSystem<AnimationSystem>();
	AddSystem<RenderSystem>();
}
Scene::Scene(std::string name) {
	m_name = name;
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();
	AddSystem<AnimationSystem>();
	AddSystem<RenderSystem>();


}

Entity Scene::CreateEntity(std::string tag = "Entity") {
	Entity entity = { m_entities.create(), this };
	entity.Add<TagComponent>(tag);
	return entity;
}

void Scene::OnEvent(SDL_Event* event) {
	for (auto& system : m_systems) {
		system->OnEvent(event);
	}
}

void Scene::OnUpdate() {
	for (auto& system : m_systems) {
		system->OnUpdate();
	}
}

void Scene::OnRender(Renderer& renderer) {
	for (auto& system : m_systems) {
		system->OnRender(renderer);
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