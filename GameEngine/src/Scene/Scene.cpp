#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"


namespace ProjectAlpha {
Scene::Scene() {

	AddSystem<RenderSystem>();
	AddSystem<ScriptSystem>();
	//AddSystem<MovementSystem>();
	//AddSystem<CollisionSystem>();


}

Entity Scene::CreateEntity(std::string tag = "Entity") {
	Entity entity = { m_entities.create(), this };
	entity.Add<TagComponent>(tag);
	return entity;
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

} //END namespace ProjectAlpha