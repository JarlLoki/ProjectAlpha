#include "TestGame.h"


class MenuScript : public ProjectAlpha::Script {

	void OnEvent(SDL_Event* event) override {
		//On Mouse Click
			//Check if click is over a menu,
			//if its on button 1:
				//Start Game!
					//Load Game play scene
					//Set gameplay scene as active
		
	}

	void OnUpdate() override {

	}
};


void LoadMenuScene(ProjectAlpha::Scene& scene) {

	//Button 1
	{
		auto button = scene.CreateEntity("Button1");
		auto transform = button.Add<Components::Transform>();
		auto square = button.Add<ProjectAlpha::SquareComponent>();


	}

	//Button 2
	{

	}


}

class MenuScene : public ProjectAlpha::Scene {
	MenuScene() : Scene("Menu") {
		//Button 1
		{
			auto button = CreateEntity("Button1");
		}


	}


};