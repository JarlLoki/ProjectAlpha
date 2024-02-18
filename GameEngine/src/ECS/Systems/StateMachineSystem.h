#pragma once
#include "ECS/System.h"
#include "ECS/Components/StateMachineComponent.h"
namespace ProjectAlpha {

struct StateMachineSystem : public System {
	void OnUpdate() override {
		auto entities = m_scene->GetEntitiesWith<StateMachineComponent>();
		for (auto entityID : entities) {
			Entity entity = { entityID, m_scene };
			auto& stateMachine = entity.Get<StateMachineComponent>();
			stateMachine.GetState().OnUpdate();
		}
	}

	void OnEvent(SDL_Event* event) override {
		auto entities = m_scene->GetEntitiesWith<StateMachineComponent>();
		for (auto entityID : entities) {
			Entity entity = { entityID, m_scene };
			auto& stateMachine = entity.Get<StateMachineComponent>();
			stateMachine.GetState().OnEvent(event);
		}
	}

};



}//END namespace ProjectAlpha