#pragma once
#include "ProjectAlpha.h"

struct WSADControlScript : public ProjectAlpha::Script {
	void OnUpdate() override {

		auto& physics = m_entity.Get<Components::Physics>();

		auto keys = SDL_GetKeyboardState(NULL);
		ProjectAlpha::Vector2D dir = 0;

		if (keys[SDL_SCANCODE_W]) dir.y -= 1;
		if (keys[SDL_SCANCODE_S]) dir.y += 1;
		if (keys[SDL_SCANCODE_A]) dir.x -= 1;
		if (keys[SDL_SCANCODE_D]) dir.x += 1;

		physics.Direction = dir;

	}
};

struct CameraZoomScript : public ProjectAlpha::Script {

	void OnEvent(SDL_Event* event) override {
		switch (event->type) {
		case SDL_KEYDOWN:
			if (event->key.repeat == 0) {
				switch (event->key.keysym.sym) {
				case SDL_KeyCode::SDLK_UP:
				{
					auto& camera = m_entity.Get<Components::Camera>();
					camera.ZoomScale += 0.5f;
				}
				break;

				case SDL_KeyCode::SDLK_DOWN:
				{
					auto& camera = m_entity.Get<Components::Camera>();
					camera.ZoomScale -= 0.5f;
				}
				break;
				}
			}
			break;
		}
	}
};

class GameScript : public ProjectAlpha::Script {
	void OnEvent(SDL_Event* event) override {
		//On Mouse Click
			//Check if click is over a menu,
			//if its on button 1:
				//Start Game!
					//Load Game play scene
					//Set gameplay scene as active


		//Temp:
		//On keypress:
		switch (event->type) {
		case SDL_KEYDOWN:
			if (event->key.repeat == 0) {
				switch (event->key.keysym.sym) {
				case SDL_KeyCode::SDLK_F1:
				{
					m_game->Scenes.SetCurrentScene("Menu");
				}
				break;
				}
			}
		}

	}

	void OnUpdate() override {

	}
};