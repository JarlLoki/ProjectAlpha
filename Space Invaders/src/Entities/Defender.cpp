#include "Defender.h"
#include "bullet.h"

namespace Entities::Defender {

namespace Scripts {
//-----------------
//| DefenderLogic |
//-----------------
////////////////////////////////////////////////////////////////////////////////
// Logic for the Defender Entity
// --OnEvent: 
//   -updates when the spacebar is pressed it will shoot a bullet
// --OnUpdate: 
//   -updates the collider rect
//   -moves the entity left or right if a/d or left/right arrow is held down
//	 -keeps the entity on the screen
////////////////////////////////////////////////////////////////////////////////
struct DefenderLogic : public PA::Script {

	//OnEvent: 
    //-updates when the spacebar is pressed it will shoot a bullet
	void OnEvent(SDL_Event* event) override {
		if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
			switch (event->key.keysym.sym) {

			case SDLK_SPACE:
				if (m_entity.Get<Components::Animator>().GetAnimationID() ==
					Defender::Animations::idle) {
				
					auto bullet = Entities::Bullet::Create(m_entity.GetScene());

					auto defenderPos = m_entity.Get<Components::Transform>().Position;
					defenderPos.y -= 8;
					bullet.Get<Components::Transform>().Position = defenderPos;
					bullet.Get<Components::Physics>().Direction.y = -1.0f;
					bullet.Get<Components::Physics>().Speed = 8;

					//Play shooting sound:
					m_game->AudioAssets.PlaySound(Sounds::Shooting);
				}
				break;
			}
		}
	}

	//OnUpdate: 
	//-updates the collider rect
	//-moves the entity left or right if a/d or left/right arrow is held down
	//-keeps the entity on the screen
	void OnUpdate() override {
		/*
		* TODO:
		* Is this needed? Defender's hitbox never really changes
		* this should probably be set once instead of updating
		* each frame for no reason
		*/
		//Update Collider with the sprite binding box
		const auto& sprite = m_entity.Get<Components::Sprite>();
		auto& collider = m_entity.Get<Components::Collider>();
		collider.rect = sprite.Sprite.BindingBox;


		//Update Direction
		int dir = 0;
		if (PA::Input::Keyboard::IsPressed(SDL_SCANCODE_A) ||
			PA::Input::Keyboard::IsPressed(SDL_SCANCODE_LEFT)) {
			dir--;
		}
		if (PA::Input::Keyboard::IsPressed(SDL_SCANCODE_D) ||
			PA::Input::Keyboard::IsPressed(SDL_SCANCODE_RIGHT)) {
			dir++;
		}
		auto& transform = m_entity.Get<Components::Transform>();
		auto& physics = m_entity.Get<Components::Physics>();

		//Apply velocity to the position:
		//physics.Direction.x = dir;
		auto& animator = m_entity.Get<Components::Animator>();
		if (m_entity.Get<Components::Animator>().GetAnimationID() == 
			Animations::idle) {
			transform.Position.x += dir * physics.Speed;//
		}

		//Keep Defender on the screen:
		if (transform.Position.x <= 0) {
			transform.Position.x = 0;
	
		}
		int width = m_game->GetRenderer().GetLogicalRenderSize().w;
		if(transform.Position.x+32 >= width) {
			transform.Position.x = (float)(width - 32);
		}

		//If death animation is playing and it reaches its end then
		//change the animation to dead
		if (animator.GetAnimationID() == Animations::death &&
			animator.End()) {
			animator.Start(Animations::dead, false);
		}

	}
};
} //END namespace Scripts
//--------------
//| InitAssets |
//--------------
////////////////////////////////////////////////////////////////////////////////
// Initiates the assets for the Defender entity
////////////////////////////////////////////////////////////////////////////////
void InitAssets() {
	//Graphics
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Idle);
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Death);
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Dead);

	//Sounds
	PA::Game::AudioAssets.LoadSound(Sounds::Shooting);
}

//----------
//| Create |
//----------
////////////////////////////////////////////////////////////////////////////////
// Creates the Defender Entity
// -Takes a pointer to the scene that will be creating it and add its to the
// entity Registery of that scene
// -Returns the created Entity as well
////////////////////////////////////////////////////////////////////////////////
ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene) {
	auto defender = scene->CreateEntity(Defender::Name);

	defender.Add<Components::Transform>(250 - 16, 500);
	auto& physics = defender.Add<Components::Physics>();
	physics.Speed = 2;

	//States
	////////////////
	//defender.Add<Components::StateMachine>(defender);

	//Sprite and Animations:
	////////////////
	//Load Assets:
	

	//Add Components:
	auto& sprite = defender.Add<Components::Sprite>();
	auto& animator = defender.Add<Components::Animator>();

	//Create Animations
	PA::AnimationProperties animProps;
	animProps.FrameWidth = 32;
	animProps.FrameHeight = 32;
	animProps.FrameDelay = 100;

	//Idle
	animProps.SpriteSheet = SpriteSheets::Idle;
	animProps.NumOfFrames = 1;
	animProps.AnimationID = Animations::idle;
	//animator.Animations[Animations::idle] = { animProps };
	animator.Add(animProps);

	//Death
	animProps.SpriteSheet = SpriteSheets::Death;
	animProps.NumOfFrames = 6;
	animProps.AnimationID = Animations::death;
	animator.Add(animProps);

	//Dead
	animProps.SpriteSheet = SpriteSheets::Dead;
	animProps.NumOfFrames = 1;
	animProps.AnimationID = Animations::dead;
	animator.Add(animProps);

	//Set the first starting animation
	animator.Start(Animations::idle, true);

	//Collider
	////////////////
	auto& collider = defender.Add<Components::Collider>();
	collider.Tag = Defender::Name;
	collider.IsSold = false;

	//Scripts
	////////////////
	auto& scripts = defender.Add<Components::Script>(defender);
	scripts.Add<Scripts::DefenderLogic>();

	return defender;
}

}//END namespace Defender