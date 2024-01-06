#include "TestGame.h"


struct WSADControlScript : public ProjectAlpha::Script {
	void OnUpdate() override {

		auto& physics = m_entity.Get<Components::Physics>();

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
		switch (event->type) {
		case SDL_KEYDOWN:
			if (event->key.repeat == 0) {
				switch (event->key.keysym.sym) {
				case SDL_KeyCode::SDLK_UP:
				{
					auto& camera = m_entity.Get<Components::Camera>();
					camera.ZoomScale += 0.1f;
				}
				break;

				case SDL_KeyCode::SDLK_DOWN:
				{
					auto& camera = m_entity.Get<Components::Camera>();
					camera.ZoomScale -= 0.1f;
				}
				break;
				}
			}
			break;
		}
	}
};



TestGame::TestGame() {
	using namespace ProjectAlpha;

	/*Make BLue Square*/ {
		auto player = this->GetScene().CreateEntity("player");
		auto& transform = player.Add<TransformComponent>(100.0f, 100.0f);
		auto& square = player.Add<SquareComponent>();
		square.color = { 0,255,255, 0 };
		square.height = 100;
		square.width = 100;

		auto& physics = player.Add<PhysicsComponent>();
		physics.Speed = 5;

		auto& cameraComp = player.Add<CameraComponent>();
		cameraComp.ZoomScale = 1;
		cameraComp.offSet = { square.width / 2, square.height / 2 };
		auto& scripts = player.Add<ScriptComponent>(player);
		scripts.Add<WSADControlScript>();
		scripts.Add<CameraZoomScript>();




	}

	/*Make orange square*/ {
		auto boo = this->GetScene().CreateEntity("boo");
		auto& transform = boo.Add<TransformComponent>(400.0f, 400.0f);
		auto& square = boo.Add<SquareComponent>();
		square.color = { 255, 100, 0, 0 };
		square.width = 100;
		square.height = 30;
	}

	/*Create Camera*/ {
		auto camera = this->GetScene().CreateEntity("camera");
		auto& transform = camera.Add<TransformComponent>(0.0f, 0.0f);
		transform.Scale = 1;
		auto& physics = camera.Add<PhysicsComponent>();
		physics.Speed = 5;

		/*
		auto& cameraComp = camera.Add<CameraComponent>();
		cameraComp.ZoomScale = 1;
		cameraComp.ViewWidth = GetRenderer().GetViewPortWidth();
		cameraComp.ViewHeight = GetRenderer().GetViewPortHeight();
		auto& scripts = camera.Add<ScriptComponent>(camera);
		scripts.Add<WSADControlScript>();
		scripts.Add<CameraZoomScript>();
		*/
		
	}


}
