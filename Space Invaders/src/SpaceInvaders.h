#pragma once
#include "ProjectAlpha.h"

#include "Scenes/InvaderScenes.h"

class SpaceInvaders : public ProjectAlpha::Game {
public:
	//Initalization Here
	SpaceInvaders() {
		//Load Scene:
		//this->Scenes.LoadScene<Scenes::Level1>();
		//this->Scenes.SetCurrentScene()

		Scenes.AddScene(Scenes::Level1::CreateScene());
		Scenes.SetCurrentScene(Scenes::Level1::SceneID);

	}

	int Lives = 3;
	int Level = 0;
	int Score = 0;
};