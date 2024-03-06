#pragma once
#include "ProjectAlpha.h"

#include "Layers/MenuLayer.h"
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

const std::string LayerName = "GameLayer";
class GamePlayLayer : public PA::Layer {
public:
	GamePlayLayer(std::string name = LayerName) : Layer(LayerName) {}

	void OnAttach() override {
		Scenes.AddScene(Scenes::Level1::CreateScene());
		Scenes.SetCurrentScene(Scenes::Level1::SceneID);
	}

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

		Layers.AddLayer(new GamePlayLayer());
		Layers.AddLayer(new Layers::Menu::MenuLayer());
		Layers[Layers::Menu::LayerName]->Scenes.GetCurrentScene()->Hide();
		
		m_renderer.LoadAllTexturesFromImages(ImageAssets);
	}

	void OnEvent(SDL_Event* event) override {
		switch (event->type) {
		case SDL_WINDOWEVENT:			
			if (event->window.event == SDL_WINDOWEVENT_FOCUS_LOST) {

				Layers[LayerName]->Scenes.GetCurrentScene()->Pause();
				Layers[Layers::Menu::LayerName]->Scenes.GetCurrentScene()->Show();
			}
			
			if (event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {

				Layers[LayerName]->Scenes.GetCurrentScene()->Resume();
				Layers[Layers::Menu::LayerName]->Scenes.GetCurrentScene()->Hide();
			}

			break;
		case SDL_KEYDOWN:
			//On first key press, then ignores key being held:
			if (event->key.repeat == 0) {
				switch (event->key.keysym.sym) {

					//Toggle drawing hitboxes
				case SDLK_ESCAPE:
					this->m_isRunning = false;
					break;
				//RESET:
				case SDLK_r:
					Layers[LayerName]->Scenes.AddScene(Scenes::Level1::CreateScene());
					Layers[LayerName]->Scenes.SetCurrentScene(Scenes::Level1::SceneID);
					break;
				//PAUSE:
				case SDLK_p:					
					Layers[LayerName]->Scenes.GetCurrentScene()->TogglePause();
					Layers[Layers::Menu::LayerName]->Scenes.GetCurrentScene()->ToggleHide();
		
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