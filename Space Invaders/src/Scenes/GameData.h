#pragma once
#include "ProjectAlpha.h"

namespace Scenes::GameData {

const std::string SceneID = "GameData";

auto Create() {
	ProjectAlpha::Scene* scene = new ProjectAlpha::Scene(SceneID);
	
	auto playerLives = scene->CreateEntity("player_lives");


	return scene;
}

}//END namespace Scenes::GameData 