#include "Game.h"

namespace ProjectAlpha {
ImageManager Game::ImageAssets;

Game::Game() {
	Init();
}

void Game::Init() {
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
		}

		//Window Events:
		m_window.OnEvent(event);

		//Scene Events:
		Scenes.GetCurrentScene()->OnEvent(&event);

		//Key Presses:
		

	}




}

void Game::Update() {

	m_window.OnUpdate();

	Scenes.GetCurrentScene()->OnUpdate();
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
