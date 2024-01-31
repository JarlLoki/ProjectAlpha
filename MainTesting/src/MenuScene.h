#include "ProjectAlpha.h"

class MenuScript : public ProjectAlpha::Script {
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
				case SDL_KeyCode::SDLK_F2:
				{
					m_game->Scenes.SetCurrentScene("Test");
				}
				break;
				}
			}
		}
		
	}

	void OnUpdate() override {

	}
};


class TestGame;

class MenuScene : public ProjectAlpha::Scene {
public:
	MenuScene(TestGame* Game);


};
