#pragma once
#include "ProjectAlpha.h"

#include "Scenes/Menu.h"

namespace Layers::Menu {

const std::string LayerName = "Menu";

class MenuLayer : public PA::Layer {
public:
	MenuLayer() : Layer(LayerName) {
		//Add and create Menu Scene
		Scenes.AddScene(Scenes::Menu::CreateScene());
		Scenes.SetCurrentScene(Scenes::Menu::SceneID);
	}

};

}