#pragma once
//#include "ECS\entity.h"
#include "ECS/Entity.h"
#include "Script.h"

namespace ProjectAlpha {
struct ScriptComponent {
public:
	ScriptComponent(Entity entity) : m_entity(entity) {}
	~ScriptComponent() = default;
	ScriptComponent(const ScriptComponent&) = delete;

	void OnEvent(SDL_Event* event) {
		for (auto& script : m_scripts) {
			script->OnEvent(event);
		}
	}

	void OnUpdate() {
		for (auto& script : m_scripts) {
			script->OnUpdate();
		}
	}

	template <typename T, typename... TArgs>
	void Add(TArgs&&... mArgs);

	template <typename T>
	void Remove();

	template <typename T>
	auto& Get();

	template <typename T>
	bool Has();

private:
	std::vector<std::unique_ptr<Script>> m_scripts;
	Entity m_entity;
};

//Add
///////////////
template<typename T, typename... TArgs>
inline void ScriptComponent::Add(TArgs&&... mArgs) {
	std::unique_ptr<Script> script = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
	script->m_entity = m_entity;
	script->m_type = typeid(T).name();
	script->OnInit();
	m_scripts.push_back(std::move(script));
}

//Remove
/////////////
template<typename T>
inline void ScriptComponent::Remove() {
	std::string typeToRemove = typeid(T).name();
	auto remove = [](std::unique_ptr<Script> script) {
		if (script->m_type == typeToRemove)
			return true;
		else
			return false;
		};

	m_scripts.erase(
		std::remove_if(std::begin(m_scripts), std::end(m_scripts), remove),
		std::end(m_scripts)
	);
}
//Get
/////////////
template<typename T>
inline auto& ScriptComponent::Get() {
	std::string typeToFind = typeid(T).name();

	for (auto& script : m_scripts) {
		if (script->m_type == typeToFind) {
			return script;
		}
	}
}
//Has
/////////////
template<typename T>
inline bool ScriptComponent::Has() {
	std::string hasType = typeid(T).name();
	for (auto& script : m_scripts) {
		if (script->m_type == hasType)
			return true;
	}
	return false;
}

}//end namespace 