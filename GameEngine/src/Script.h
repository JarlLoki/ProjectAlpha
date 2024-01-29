#pragma once
#include <string>
#include "Scene/Entity.h"

namespace ProjectAlpha{
struct ScriptComponent;
class Game;

struct Script {
	Script() = default;
	~Script() = default;
	//Entity entity;

	virtual void OnInit() {}
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnUpdate() {}
	virtual void OnDestroy() {}

protected:
	std::string m_type;
	Entity m_entity;
	
	static Game* m_game;
	friend Game;

	friend ScriptComponent;
};

}//END namespace ProjectAlpha