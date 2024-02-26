#pragma once
#include "ProjectAlpha.h"
#include "Entities/Entities.h"

namespace Scenes::Level1 {
const std::string SceneID = "Level1";

auto CreateScene() {

	auto scene = std::make_shared<PA::Scene>(PA::Scene(SceneID));
	//Init Assets:

	
	//Init Background:


	//Create Camera:
	auto camera = scene->CreateEntity("Camera");
	camera.Add<Components::Transform>(0, 0);
	camera.Add<Components::Camera>();

	//Create Invader Group:
	auto invaderGroup = Entities::InvaderGroup::Create(scene.get(), {5,4});

	//Create the Defender:
	auto defender = Entities::Defender::Create(scene.get());


	return scene;
}





class Level1 : public ProjectAlpha::Scene {
	Level1() : Scene("Level_1") {
		//Init Assets:


		//Init background:


		//Create Camera:
		auto camera = this->CreateEntity("Camera");
		camera.Add<Components::Transform>(0, 0);
		camera.Add<Components::Camera>();

		//Create Invader Group:
		auto invaderGroup = Entities::InvaderGroup::Create(this, { 5,4});


		//Create the Defender:
		auto defender = Entities::Defender::Create(this);

	}

};
}