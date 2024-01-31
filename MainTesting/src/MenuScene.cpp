#include "MenuScene.h"

#include "TestGame.h"



MenuScene::MenuScene(TestGame* game) : Scene("Menu") {
	int winW = game->GetWindow().GetWidth();
	int winH = game->GetWindow().GetHeight();

	int buttonW = 200;
	int buttonH = 50;

	int buttonNum = 3;
	int buttonPadding = 50;

	int buttonX = (winW - buttonW) / 2;

	int groupH = (buttonH * buttonNum) + (buttonPadding * (buttonNum - 1));
	int groupY = (winH - groupH) / 2;


	int buttonCurr = 0;

	/*
	{//Test
		auto button = CreateEntity("Test");
		auto& transform = button.Add<Components::Transform>();
		auto& square = button.Add<ProjectAlpha::SquareComponent>();

		transform.Position.x = 0;
		transform.Position.y = 0;

		square.color = { 0,255,255, 0 };
		square.width = 100;
		square.height = 100;
	}
	//*/
	{
		auto menuLogic = CreateEntity("MenuLogic");
		auto& scripts = menuLogic.Add<ProjectAlpha::ScriptComponent>(menuLogic);
		scripts.Add<MenuScript>();
	}


	{//Button1
		auto button = CreateEntity("Button1");
		auto& transform = button.Add<Components::Transform>();
		auto& square = button.Add<ProjectAlpha::SquareComponent>();

		transform.Position.x = buttonX;
		transform.Position.y = groupY;

		square.color = { 0,255,255, 0 };
		square.width = buttonW;
		square.height = buttonH;

		buttonCurr++;
	}

	{//Button2
		auto button = CreateEntity("Button2");
		auto& transform = button.Add<Components::Transform>();
		auto& square = button.Add<ProjectAlpha::SquareComponent>();

		transform.Position.x = buttonX;
		transform.Position.y = groupY + (buttonH * buttonCurr) + (buttonPadding * buttonCurr);

		square.color = { 0,255,255, 0 };
		square.width = buttonW;
		square.height = buttonH;

		buttonCurr++;
	}

	{//Button3
		auto button = CreateEntity("Button3");
		auto& transform = button.Add<Components::Transform>();
		auto& square = button.Add<ProjectAlpha::SquareComponent>();

		transform.Position.x = buttonX;
		transform.Position.y = groupY + (buttonH * buttonCurr) + (buttonPadding * (buttonCurr));

		square.color = { 0,255,255, 0 };
		square.width = buttonW;
		square.height = buttonH;

		buttonCurr++;
	}

	//Need to have a Camera Component!
	{
		auto camera = CreateEntity("Camera");
		auto& transform = camera.Add<Components::Transform>();
		//auto& physics = camera.Add<Components::Physics>();
		//auto& scripts = camera.Add<ProjectAlpha::ScriptComponent>(camera);

		transform.Position = { 0.0f, 0.0f };
		auto& cameraC = camera.Add<Components::Camera>();


	}
}