#pragma once
#include "Layer.h"
#include "Graphics/Window.h"
#include "Graphics/Renderer.h"
#include "Graphics/FontManager.h"
#include "Scene/SceneManager.h"
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

//protected:
	inline Window& GetWindow() { return m_window; }
	inline Renderer& GetRenderer() { return m_renderer; }

	SceneManager Scenes;

private:
	void Init();

	void Event();
	void Update();
	void Render();


private:
	Window m_window;
	Renderer m_renderer;

	bool m_isRunning = true;
	
};

}