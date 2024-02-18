#pragma once
#include <memory>

#include "ECS/Entity.h"

namespace ProjectAlpha {
struct StateMachineComponent;
using StateID = std::int16_t;
using ActionID = std::int16_t;

class State {
public:
	State(StateID id) :
		m_id(id)
	{}

	void Init(StateMachineComponent* machine, Entity entity) {
		m_stateMachine = machine;
		m_entity = entity;
	}
	bool IsValid() { if (m_stateMachine) return true; else return false; }

	StateID GetID() { return m_id; }

	virtual void OnStart() {}
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnAction(ActionID action) {}
	virtual void OnUpdate() {}
	virtual void OnExit() {}

protected:
	StateID m_id = 0;
	Entity m_entity;
	StateMachineComponent* m_stateMachine = nullptr;
};

}//END namespace ProjectAlpha