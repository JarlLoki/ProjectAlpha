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
				
					auto& transform = m_entity.Get<Components::Transform>();
					auto& camera = m_entity.Get<Components::Camera>();

					const float viewPortW = static_cast<float>(m_renderer.GetViewPortWidth());
					const float viewPortH = static_cast<float>(m_renderer.GetViewPortHeight());
					
					int cW = (camera.ViewWidth / 2);
					int cH = (camera.ViewHeight / 2);

					camera.ZoomScale += 0.1f;
					transform.Scale = viewPortW / (viewPortW * camera.ZoomScale);

					camera.ViewWidth = viewPortW * transform.Scale;
					camera.ViewHeight = viewPortH * transform.Scale;


					int newCW = (camera.ViewWidth / 2);
					int newCH = (camera.ViewHeight / 2);

					int xOffset = cW - newCW;
					int yOffset = cH - newCH;

					transform.Position.x += xOffset;
					transform.Position.y += yOffset;
					//*/

				
				}
				break;

				case SDL_KeyCode::SDLK_DOWN:
				{
					auto& entities = m_scene.GetEntities();
					auto view = entities.view<CameraComponent, TransformComponent>();
					for (auto entity : view) {
						auto& transform = view.get<TransformComponent>(entity);
						auto& camera = view.get<CameraComponent>(entity);

						const float viewPortW = static_cast<float>(m_renderer.GetViewPortWidth());
						const float viewPortH = static_cast<float>(m_renderer.GetViewPortHeight());

						int cW = (camera.ViewWidth / 2);
						int cH = (camera.ViewHeight / 2);

						camera.ZoomScale -= 0.1f;

						transform.Scale = viewPortW / (viewPortW * camera.ZoomScale);
						camera.ViewWidth = viewPortW * transform.Scale;
						camera.ViewHeight = viewPortH * transform.Scale;
						int newCW = (camera.ViewWidth / 2);
						int newCH = (camera.ViewHeight / 2);

						int xOffset = cW - newCW;
						int yOffset = cH - newCH;

						transform.Position.x += xOffset;
						transform.Position.y += yOffset;

					}
				}
				break;
				}
			}
			break;
		}

	}

	void OnUpdate() override {

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
		physics.Speed = 10;
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
		auto& Physics = camera.Add<PhysicsComponent>();
		auto& cameraComp = camera.Add<CameraComponent>();
		cameraComp.ZoomScale = 1;
		cameraComp.ViewWidth = GetRenderer().GetViewPortWidth();
		cameraComp.ViewHeight = GetRenderer().GetViewPortHeight();
		auto& scripts = camera.Add<ScriptComponent>(camera);
		scripts.Add<WSADControlScript>();
		GetWindow().GetWidth();
		
	}


}
