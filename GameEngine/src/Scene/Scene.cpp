#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "CollisionSystem.h"
#include "MovementSystem.h"

namespace ProjectAlpha {
Scene::Scene() {
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();

	AddSystem<RenderSystem>();
}
Scene::Scene(std::string name) {
	m_name = name;
	AddSystem<ScriptSystem>();
	AddSystem<MovementSystem>();
	AddSystem<CollisionSystem>();

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

} //END namespace ProjectAlpha