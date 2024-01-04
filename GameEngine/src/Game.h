#pragma once
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Scene/Components.h"
#include "Scene/System.h"
#include "Script.h"

#include "Log.h"

namespace ProjectAlpha {

class Game {
public:
	Game();

	void Run();

protected:
	inline Window& GetWindow() { return m_window; }
	inline Renderer& GetRenderer() { return m_renderer; }
	inline Scene& GetScene() { return m_scene; }


private:
	void Init();

	void Event();
	void Update();
	void Render();


private:
	Window m_window;
	Renderer m_renderer;
	Scene m_scene;

	bool m_isRunning = true;
	
};

}