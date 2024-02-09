#pragma once
#include "SDL.h"

namespace ProjectAlpha {
class Game;
class Scene;
class Renderer;

struct System {
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnUpdate() {}
	virtual void OnRender(Renderer& renderer) {}

private:
	static void Init(Game* game) { m_game = game; }

protected:
	Scene* m_scene;

	static Game* m_game;


	friend Scene;
	friend Game;
};

}//END namespace ProjectAlpha