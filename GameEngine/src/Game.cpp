#include "Game.h"
//#include "Log.h"

namespace ProjectAlpha {
Game::Game() {

	Init();
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
	m_scene.OnUpdate();

	auto& entities = m_scene.GetEntities();
	//Update Player Movement
	/*
	auto keys = SDL_GetKeyboardState(NULL);

	auto& entities = m_scene.GetEntities();
	auto view = entities.view<TagComponent, PhysicsComponent>();
	for (auto entity : view) {
		auto& tag = view.get<TagComponent>(entity);
		auto& physics = view.get<PhysicsComponent>(entity);
		if (tag.GetTag() == "camera") {
			Vector2D dir;
			//Apply Up Direction
			if (keys[SDL_SCANCODE_W]) dir.y -= 1;
			if (keys[SDL_SCANCODE_S]) dir.y += 1;
			if (keys[SDL_SCANCODE_A]) dir.x -= 1;
			if (keys[SDL_SCANCODE_D]) dir.x += 1;

			physics.Direction = dir;
		}
	}

	{
		auto& entities = m_scene.GetEntities();
		auto view = entities.view<CameraComponent, TransformComponent>();
		for (auto entity : view) {
			
		}

	}
	*/

	//Move Objects
	//auto& entities = m_scene.GetEntities();

	auto view2 = entities.view<TransformComponent, PhysicsComponent>();
	for (auto entity : view2) {
		auto& transform = view2.get<TransformComponent>(entity);
		auto& physics = view2.get<PhysicsComponent>(entity);

		physics.Direction.Normalize();
		Vector2D velocity = physics.Direction * physics.Speed;

		if (physics.IsMovable) {
			transform.Position += velocity;
		}

	}


}

void Game::Render() {

	//Reset Render Buffer
	m_renderer.ResetDrawBuffer();

	//Draw 
	//example:
	//this->entities->Draw(m_renderer);
	//or
	//m_renderer.DrawEntities(entities);
	auto& entities = m_scene.GetEntities();

	//Draw Squares

	m_scene.OnRender(m_renderer);



	//Draw to window
	m_renderer.DrawBufferToWindow();
}

 
}
