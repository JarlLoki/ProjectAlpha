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
					camera.ZoomScale += 0.5f;
				}
				break;

				case SDL_KeyCode::SDLK_DOWN:
				{
					auto& camera = m_entity.Get<Components::Camera>();
					camera.ZoomScale -= 0.5f;
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

	//Load Fonts
	this->GetRenderer().Fonts.LoadFont("assets/fonts/arial/arial", 24);
	this->GetRenderer().Fonts.SetDefaultFont("assets/fonts/arial/arial", 24);



	/*Make BLue Square*/ {
		auto player = this->GetScene().CreateEntity("player");
		auto& transform = player.Add<TransformComponent>();
		transform.Position = { 100.0f, 100.0f };
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

		auto& collider = player.Add<ColliderComponent>();
		collider.rect = { 0, 0, square.width, square.height };
		
	}

	/*Make orange square*/ {
		auto boo = this->GetScene().CreateEntity("boo");
		auto& transform = boo.Add<TransformComponent>();
		transform.Position = { 400.0f, 400.0f };
		auto& square = boo.Add<SquareComponent>();
		square.width = 200;
		square.height = 80;
		square.color = { 255, 100, 0, 0 };
		//square.width = 100;
		//square.height = 30;
		auto& text = boo.Add<TextComponent>();
		text.Text = "This is a test on text 094335";
		text.FontName = "arial";
		text.FontSize = 24;
		text.Color = { 255, 255, 255, 0 };
		text.RenderedText = GetRenderer().RenderText({text.FontName, text.FontSize, 
													  text.Text, text.Color});


		//square.width = text.RenderedText->GetWdith() +1;
		//square.height = text.RenderedText->GetHeight()+1;

		auto& collider = boo.Add<ColliderComponent>();
		collider.rect = { 0, 0, square.width, square.height };

		auto& physics = boo.Add <PhysicsComponent>();
		physics.IsMovable = false;

	}

	/*Create Camera*/ {
		auto camera = this->GetScene().CreateEntity("camera");
		auto& transform = camera.Add<TransformComponent>();

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

	/*Text Text*/ {
		auto entity = this->GetScene().CreateEntity("text");
		auto& transform = entity.Add<Components::Transform>(100.0f, 100.0f);
		//transform.Position = {100.0f, 100/}
		auto& text = entity.Add<Components::Text>();
		text.Position = 0;
		text.Text = "Hello World!";
		text.FontName = "arial";
		text.FontSize = 24;
		text.Color = { 255, 255, 255, 0 };
		
	}


}
