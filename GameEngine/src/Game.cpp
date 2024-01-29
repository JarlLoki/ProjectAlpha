#include "Game.h"
//#include "Log.h"

namespace ProjectAlpha {
Game::Game() {

	Init();

	//Initilize scripts:
	Script::m_game = this;
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
		Render();

		delay_ticks = SDL_GetTicks() - starting_ticks;
		if ((frame_delay / target_fps) > delay_ticks)
			SDL_Delay(frame_delay / target_fps - delay_ticks);
	}
}


void Game::Init() {
	//Set Renderer to window
	m_renderer.SetRenderWindowTarget(m_window);

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
		m_scene.OnEvent(&event);


		//Key Presses:
		

	}




}

void Game::Update() {

	m_window.OnUpdate();

	auto& entities = m_scene.GetRegistry();

	m_scene.OnUpdate();
}

void Game::Render() {

	//Reset Render Buffer
	m_renderer.ResetDrawBuffer();

	//Draw 
	//example:
	//this->entities->Draw(m_renderer);
	//or
	//m_renderer.DrawEntities(entities);
	auto& entities = m_scene.GetRegistry();

	//Draw Squares

	m_scene.OnRender(m_renderer);



	//Draw to window
	m_renderer.DrawBufferToWindow();
}

 
}
