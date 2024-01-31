#include "TestScene2.h"
#include "TestGame.h"
#include "GameScripts.h"

TestScene2::TestScene2(TestGame* game) : Scene("Test2") {

	//Make BLue Square
	{
		auto player = CreateEntity("player");
		auto& transform = player.Add<Components::Transform>();
		transform.Position = { 201.0f, 100.0f };
		auto& square = player.Add<ProjectAlpha::SquareComponent>();
		square.color = { 0,255,255, 0 };
		square.height = 100;
		square.width = 50;

		auto& physics = player.Add<ProjectAlpha::PhysicsComponent>();
		physics.Speed = 1;

		auto& cameraComp = player.Add<ProjectAlpha::CameraComponent>();
		cameraComp.ZoomScale = 4;
		cameraComp.offSet = { square.width / 2, square.height / 2 };
		cameraComp.Center = true;
		auto& scripts = player.Add<ProjectAlpha::ScriptComponent>(player);
		scripts.Add<WSADControlScript>();
		scripts.Add<CameraZoomScript>();

		//auto& collider = player.Add<ProjectAlpha::ColliderComponent>();
		//collider.rect = { 0, 0, square.width, square.height };

	}

	{///Make orange square
		auto boo = CreateEntity("boo");
		auto& transform = boo.Add<ProjectAlpha::TransformComponent>();
		transform.Position = { 250.0f, 100.0f };
		auto& square = boo.Add<ProjectAlpha::SquareComponent>();
		square.width = 200;
		square.height = 80;
		square.color = { 255, 100, 0, 0 };
		//square.width = 100;
		//square.height = 30;
		auto& text = boo.Add<ProjectAlpha::TextComponent>();
		text.Text = "This is a test on text 094335";
		text.FontName = "arial";
		text.FontSize = 24;
		text.Color = { 255, 255, 255, 0 };
		//text.RenderedText = game.GetRenderer().RenderText({ text.FontName, text.FontSize,
		//											  text.Text, text.Color });


		//square.width = text.RenderedText->GetWdith() +1;
		//square.height = text.RenderedText->GetHeight()+1;

		//auto& collider = boo.Add<ProjectAlpha::ColliderComponent>();
		//collider.rect = { 0, 0, square.width, square.height };

		auto& physics = boo.Add <ProjectAlpha::PhysicsComponent>();
		physics.IsMovable = false;

	}


}