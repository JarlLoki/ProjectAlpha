#pragma once
#include <string>
#include "ECS/Entity.h"

namespace ProjectAlpha{
struct ScriptComponent;
class Game;

struct Script {
	Script() = default;
	~Script() = default;
	static void Init(Game* game) { m_game = game; }
	//Entity entity;

	virtual void OnInit() {}
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnUpdate() {}
	virtual void OnDestroy() {}

protected:
	std::string m_type;
	Entity m_entity;
	
	static Game* m_game;

	friend ScriptComponent;
};

}//END namespace ProjectAlpha