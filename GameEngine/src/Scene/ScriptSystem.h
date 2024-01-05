#pragma once
#include "System.h"
#include "ScriptComponent.h"
namespace ProjectAlpha {

struct ScriptSystem : public System {

	void OnEvent(SDL_Event* event) override {
		auto view = m_scene->GetEntities().view<ScriptComponent>();
		for (auto entity : view) {
			auto& scripts = view.get<ScriptComponent>(entity);
			scripts.OnEvent(event);
		}

	}

	void OnUpdate() override {
		auto view = m_scene->GetEntities().view<ScriptComponent>();
		for (auto entity : view) {
			auto& scripts = view.get<ScriptComponent>(entity);
			scripts.OnUpdate();
		}

	}

};

}//END namespace ProjectAlpha