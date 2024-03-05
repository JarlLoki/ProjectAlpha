#include "Game.h"

namespace ProjectAlpha {
ImageManager Game::ImageAssets;
Audio::AudioMixer Game::AudioAssets;

Game::Game() {
	
	Init();
}

Game::Game(WindowProperties windowProps) : m_window(windowProps) {
	Init();
}

void Game::Init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		//Error Check
		PA_LOG_ERROR("SDL Initilization failed.");
	} else {
		SDL_version version;
		SDL_VERSION(&version);

		PA_LOG_INFO("SDL Intilized successfully.");
		PA_LOG_INFO("SDL Version: " + std::to_string(version.major) + "." +
			std::to_string(version.minor) + "." +
			std::to_string(version.patch));
	}

	//Set Renderer to window
	m_renderer.SetRenderWindowTarget(m_window);

	//Initilize Systems


	//Initilize scripts:
	Script::Init(this);
	System::Init(this);
}

void Game::Run() {
	const int target_fps = 60;
	const int frame_delay = 1000;
	Uint32 starting_ticks;
	int delay_ticks;

	while (m_isRunning) {
		starting_ticks = SDL_GetTicks();

		Event();
		Update();
		//Render();

		delay_ticks = SDL_GetTicks() - starting_ticks;
		if ((frame_delay / target_fps) > delay_ticks)
			SDL_Delay(frame_delay / target_fps - delay_ticks);
	}
}




void Game::Event() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		//System Events:
		switch (event.type) {
		case SDL_QUIT:
			m_isRunning = false;
			break;
		case SDL_KEYDOWN:
			//On first key press, then ignores key being held:
			if (event.key.repeat == 0) {
				switch (event.key.keysym.sym) {
				
				//Toggle drawing hitboxes
				case SDLK_F2:					
					m_renderer.DrawHitBoxes(!m_renderer.DrawHitBoxes());
				}

			}

		}

		//Window Events:
		m_window.OnEvent(event);

		//Game Events
		OnEvent(&event);

		//Scene Events:
		Scenes.GetCurrentScene()->OnEvent(&event);

		//Key Presses:
		

	}




}

void Game::Update() {

	m_window.OnUpdate();
	OnUpdate();
	Scenes.GetCurrentScene()->OnUpdate();
	//Scenes.GetCurrentScene()->OnRender();
	//Scenes.GetCurrentScene()->Cleanup();
	
}

void Game::Render() {

	//Reset Render Buffer
	m_renderer.ResetDrawBuffer();

	//Draw 
	//example:
	//this->entities->Draw(m_renderer);
	//or
	//m_renderer.DrawEntities(entities);
	//Draw Squares
	//Scenes.GetCurrentScene()->OnRender(m_renderer);

	//Draw to window
	m_renderer.DrawBufferToWindow();
}

 
}
