#pragma once
#include "ProjectAlpha.h"
#include "Entities/Entities.h"

namespace Scenes::Level1 {
const std::string SceneID = "Level1";

auto CreateScene() {

	/*this doesnt work? is it because Scene doesnt have a copy constructor?*/
	//auto scene = std::make_shared<PA::Scene>(PA::Scene(SceneID));

	//This works
	auto scene = std::shared_ptr<PA::Scene>(new PA::Scene(SceneID));

	//this works	
	//auto scene = new PA::Scene(SceneID);
	 
	
	//Init Assets:
	Entities::LevelBackground::InitAssets();
	Entities::Defender::InitAssets();
	Entities::Bullet::InitAssets();
	Entities::Invader::InitAssets();


	//Create Camera:
	auto camera = scene->CreateEntity("Camera");
	camera.Add<Components::Transform>(0, 0);
	camera.Add<Components::Camera>();
	
	//Create Background
	Entities::LevelBackground::Create(scene.get());

	//Create Invader Group:
	auto invaderGroup = Entities::InvaderGroup::Create(scene.get(), {10,6});

	//Create the Defender:
	auto defender = Entities::Defender::Create(scene.get());


	return scene;
}





class Level1 : public ProjectAlpha::Scene {
public:
	Level1() : Scene(SceneID) {
		//Init Assets:


		//Init background:


		//Create Camera:
		auto camera = this->CreateEntity("Camera");
		camera.Add<Components::Transform>(0, 0);
		camera.Add<Components::Camera>();

		//Create Invader Group:
		//auto invaderGroup = Entities::InvaderGroup::Create(this, { 5,4});


		//Create the Defender:
		//auto defender = Entities::Defender::Create(this);

	}

};
}