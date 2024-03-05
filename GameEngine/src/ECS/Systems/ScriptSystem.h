#pragma once
#include "ECS/System.h"
#include "ECS/Components/ScriptComponent.h"
namespace ProjectAlpha {

struct ScriptSystem : public System {

	void OnEvent(SDL_Event* event) override {
		
		auto view = m_scene->GetRegistry().view<ScriptComponent>();
		int size = (int)view.size_hint();

		for (auto entity : view) {
			auto& scripts = view.get<ScriptComponent>(entity);
			scripts.OnEvent(event);
		}

	}

	void OnUpdate() override {
		auto view = m_scene->GetRegistry().view<ScriptComponent>();
		for (auto entity : view) {
			auto& scripts = view.get<ScriptComponent>(entity);
			scripts.OnUpdate();
		}

	}

};

}//END namespace ProjectAlpha