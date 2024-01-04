#include "TestGame.h"


struct MoveScript : public ProjectAlpha::Script {
	void OnUpdate() override {

		auto& physics = m_entity.Get<ProjectAlpha::PhysicsComponent>();

		auto keys = SDL_GetKeyboardState(NULL);
		ProjectAlpha::Vector2D dir = 0;

		if (keys[SDL_SCANCODE_W]) dir.y -= 1;
		if (keys[SDL_SCANCODE_S]) dir.y += 1;
		if (keys[SDL_SCANCODE_A]) dir.x -= 1;
		if (keys[SDL_SCANCODE_D]) dir.x += 1;

		physics.Direction = dir;

	}
};

struct CameraZoomScript : public ProjectAlpha::Script {

	void OnEvent(SDL_Event* event) override {

	}

	void OnUpdate() override {

	}
};



TestGame::TestGame() {
	using namespace ProjectAlpha;

	auto player = this->GetScene().CreateEntity("player");
	auto& transform = player.Add<TransformComponent>(100.0f,100.0f);
	//transform.Position = { 100, 100 };

	
	auto& square = player.Add<SquareComponent>();
	square.color = { 0,255,255, 0 };
	square.height = 100;
	square.width = 100;

	auto& physics = player.Add<PhysicsComponent>();
	physics.Speed = 10;


	{
		auto boo = this->GetScene().CreateEntity("boo");
		auto& transform = boo.Add<TransformComponent>(400.0f, 400.0f);
		auto& square = boo.Add<SquareComponent>();
		square.color = { 255, 100, 0, 0 };
		square.width = 100;
		square.height = 30;
	}

	{
		auto camera = this->GetScene().CreateEntity("camera");
		auto& transform = camera.Add<TransformComponent>(0.0f, 0.0f);
		transform.Scale = 1;
		auto& Physics = camera.Add<PhysicsComponent>();
		auto& cameraComp = camera.Add<CameraComponent>();
		cameraComp.ZoomScale = 1;
		cameraComp.ViewWidth = GetRenderer().GetViewPortWidth();
		cameraComp.ViewHeight = GetRenderer().GetViewPortHeight();
		auto& scripts = camera.Add<ScriptComponent>(camera);
		scripts.Add<MoveScript>();
	}


}
