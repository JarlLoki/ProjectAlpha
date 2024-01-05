#pragma once
#include "SDL.h"

namespace ProjectAlpha {
class Scene;
class Renderer;

struct System {
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnUpdate() {}
	virtual void OnRender(Renderer& renderer) {}
protected:
	Scene* m_scene;

	friend Scene;
};

}//END namespace ProjectAlpha