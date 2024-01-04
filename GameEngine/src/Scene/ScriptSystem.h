#pragma once
#include "System.h"
#include "ScriptComponent.h"
namespace ProjectAlpha {

struct ScriptSystem : public System {
	void OnUpdate() override {
		auto view = m_scene->GetEntities().view<ScriptComponent>();
		for (auto entity : view) {
			auto& scripts = view.get<ScriptComponent>(entity);
			scripts.Update();
		}

	}

};

}//END namespace ProjectAlpha