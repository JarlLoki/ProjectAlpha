#pragma once
#include "SDL.h"

//#include "Layer.h"
//#include "Graphics/Graphics.h"
#include "Graphics/Window.h"
#include "Graphics/ImageManager.h"
#include "Graphics/Renderer.h"
//#include "Graphics/FontManager.h"
//#include "Graphics/TextureManager.h"
#include "ECS/SceneManager.h"
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

	//Add a layer stack?
	SceneManager Scenes;//Maybe expand the Scenemanger to be the a layer
	//TextureManager Textures;
	ImageManager ImageAssets;

private:
	void Init();

	void Event();
	void Update();
	void Render();//Get rid of this?


private:
	Window m_window;
	Renderer m_renderer;//Move this out of the game app?

	bool m_isRunning = true;
	
};

}