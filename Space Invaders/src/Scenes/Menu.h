#pragma once
#include "ProjectAlpha.h"


const int GAME_WIDTH2 = 500;
const int GAME_HEIGHT2 = 600;

namespace Scenes::Menu {

const std::string SceneID = "Menu";

auto CreateScene() {
	auto scene = std::shared_ptr<PA::Scene>(new PA::Scene(SceneID));
	
	//Create Camera:
	auto camera = scene->CreateEntity("Camera");
	camera.Add<Components::Transform>(0, 0);
	camera.Add<Components::Camera>();

	PA::Size menuSize = { 90, 40 };

	PA::Vector2D pos;
	pos.x = ((float)GAME_WIDTH2 / 2) - ((float)menuSize.w / 2);
	pos.y = ((float)GAME_HEIGHT2 / 2) - ((float)menuSize.h / 2);

	//Draw a rectangle and center it in the screen:
	auto menuFrame = scene->CreateEntity("Menu_Frame");
	auto& sqC2 = menuFrame.Add<PA::SquareComponent>();
	sqC2.width = 90;
	sqC2.height = 40;
	sqC2.color = { 0,0,0,0 };
	menuFrame.Add<Components::Transform>(pos.x, pos.y);

	auto menuBG = scene->CreateEntity("Menu_Background");	
	auto& sqC = menuBG.Add<PA::SquareComponent>();
	sqC.width = 100;
	sqC.height = 50;
	sqC.color = { 255,255,255,0 };
	PA::Vector2D pos2;
	pos2.x = ((float)GAME_WIDTH2 / 2) - ((float)sqC.width / 2);
	pos2.y = ((float)GAME_HEIGHT2 / 2) - ((float)sqC.height / 2);
	menuBG.Add<Components::Transform>(pos2.x, pos2.y);



	return scene;
}

}