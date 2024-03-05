#pragma once
#include "ProjectAlpha.h"

#include "Scenes/InvaderScenes.h"

const int GAME_WIDTH = 500;
const int GAME_HEIGHT = 600;


PA::WindowProperties windowProps = {
	"Space Invaders",
	GAME_WIDTH, GAME_HEIGHT,
	false,
	true,
	true
};


class SpaceInvaders : public ProjectAlpha::Game {
public:
	//Initalization Here
	SpaceInvaders() : Game(windowProps) {
		//Set the game logical resolution:
		m_renderer.SetLogicalRenderSize(GAME_WIDTH, GAME_HEIGHT);
		


		//Calculate window size:
		//Get System desktop resolution:
		auto desktopReso = PA::GetDesktopDisplayResolution();
		//Set game window height to 80% of the desktop resolution:
		int winH = desktopReso.h * 0.83;
		int winW = winH * ((float)GAME_WIDTH / (float)GAME_HEIGHT);
		m_window.SetSize(winW, winH);


		//Load Scene:
		//this->Scenes.LoadScene<Scenes::Level1>();
		//this->Scenes.SetCurrentScene()

		Scenes.AddScene(Scenes::Level1::CreateScene());
		//Scenes.CreateScene("Level1");

		//Scenes.LoadScene<Scenes::Level1::Level1>();
		Scenes.SetCurrentScene(Scenes::Level1::SceneID);

		m_renderer.LoadAllTexturesFromImages(ImageAssets);
	}

	void OnEvent(SDL_Event* event) override {
		switch (event->type) {
		case SDL_WINDOWEVENT:			
			if(event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				Scenes.GetCurrentScene()->Pause();
			
		    if(event->window.event ==  SDL_WINDOWEVENT_FOCUS_GAINED)
				Scenes.GetCurrentScene()->Resume();
			break;
		case SDL_KEYDOWN:
			//On first key press, then ignores key being held:
			if (event->key.repeat == 0) {
				switch (event->key.keysym.sym) {

					//Toggle drawing hitboxes
				case SDLK_ESCAPE:
					this->m_isRunning = false;
					break;
				case SDLK_r:

					Scenes.AddScene(Scenes::Level1::CreateScene());
					Scenes.SetCurrentScene(Scenes::Level1::SceneID);
					break;
				case SDLK_p:
					Scenes.GetCurrentScene()->TogglePause();
					//layer[Layers::PauseSign].ToggleShow();
					//or?:
					/* example of how a layer could give a pause sign:
						if(layer[Layers::Game].GetCurrentScene().IsPaused()) {
							this->Show();
						}
						else {
							this->Hide();
						}
					*/
					break;
				}		
			}
			break;

		}
	}

	int Lives = 3;
	int Level = 0;
	int Score = 0;
};