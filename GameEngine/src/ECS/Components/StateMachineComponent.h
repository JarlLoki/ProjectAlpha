#pragma once
#include <unordered_map>
#include <memory>

#include "Log.h"
#include "Graphics/State.h"

namespace ProjectAlpha {

struct StateMachineComponent {
	StateMachineComponent(Entity entity) : m_entity(entity) {}

	template <typename T>
	void AddState();

	void SetState(StateID id);

	State& GetState();

private:
	//std::weak_ptr<State> m_currentState;
	StateID m_currentStateID = (StateID)0;
	std::unordered_map<StateID, std::shared_ptr<State>> m_states;

	Entity m_entity;
};

template<typename T>
inline void StateMachineComponent::AddState() {
	std::shared_ptr<State> state = make_shared_ptr<State>(new T);
	state->Init(this, m_entity);
	m_states[state.GetID()] = state;
}

inline void StateMachineComponent::SetState(StateID id) {
	//Check if given ID is valid and exists as a stored state:
	if (m_states[id]->IsValid()) {
		m_currentStateID = id;
	}
	else {//TODO: change this to an assert
		PA_LOG_ERROR("Given state ID does not exist.");
	}
}

inline State& StateMachineComponent::GetState() {
	return *m_states[m_currentStateID].get();
}

}//namespace ProjectAlpha