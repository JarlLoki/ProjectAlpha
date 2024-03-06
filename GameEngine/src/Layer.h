#pragma once
#include <string>

#include "SDL.h"

#include "ECS/SceneManager.h"

namespace ProjectAlpha {

class Layer {
public:
	Layer(const std::string name = "Layer") : m_name(name) {}
	virtual ~Layer() = default;
	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate() {
		Scenes.GetCurrentScene()->OnUpdate();
	}
	virtual void OnEvent(SDL_Event* event) {
		Scenes.GetCurrentScene()->OnEvent(event); 
	}

	inline const std::string& GetName() { return m_name; }

	SceneManager Scenes;
private:
	std::string m_name;

};

} //END namespace ProjectAlpha 