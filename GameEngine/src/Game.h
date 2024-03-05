#pragma once
#include "SDL.h"

//#include "Layer.h"
//#include "Graphics/Graphics.h"
#include "Graphics/Window.h"
#include "Graphics/ImageManager.h"
#include "Graphics/Renderer.h"
#include "Audio/AudioMixer.h"
//#include "Graphics/FontManager.h"
//#include "Graphics/TextureManager.h"
#include "ECS/SceneManager.h"
#include "Script.h"

#include "Log.h"

namespace ProjectAlpha {

class Game {
public:
	Game();
	Game(WindowProperties windowProps);

	void Run();

//protected:
	inline Window& GetWindow() { return m_window; }
	inline Renderer& GetRenderer() { return m_renderer; }
	//Add a layer stack?
	SceneManager Scenes;//Maybe expand the Scenemanger to be the a layer
	//TextureManager Textures;
	static ImageManager ImageAssets;
	static Audio::AudioMixer AudioAssets;

protected:
	virtual void OnEvent(SDL_Event* event) {}
	virtual void OnUpdate() {}

private:
	void Init();

	void Event();
	void Update();
	void Render();//Get rid of this?


protected:
	Window m_window;
	Renderer m_renderer;//Move this out of the game app?

	bool m_isRunning = true;
	
};

}