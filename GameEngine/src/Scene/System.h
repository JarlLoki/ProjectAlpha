#pragma once

namespace ProjectAlpha {
class Scene;
class Renderer;

struct System {
	virtual void OnEvent() {}
	virtual void OnUpdate() {}
	virtual void OnRender(Renderer& renderer) {}
protected:
	Scene* m_scene;

	friend Scene;
};

}//END namespace ProjectAlpha