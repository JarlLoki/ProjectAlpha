//#include "ProjectAlpha.h"
#include "Invader.h"
#include "Bullet.h"
#include "Defender.h"

namespace Entities::Invader {

namespace Scripts {
//------------------
//| Invalder Logic |
//------------------
////////////////////////////////////////////////////////////////////////////////
// Basic logic for the Invader:
// -Updates the colider rect
// -Also kills the Entity if the end of the Death Animation is reached
////////////////////////////////////////////////////////////////////////////////
struct InvaderLogic : public PA::Script {
	void OnUpdate() override {
		//Update Collider with the sprite binding box
		auto& sprite = m_entity.Get<Components::Sprite>();
		auto& collider = m_entity.Get<Components::Collider>();

		collider.rect = sprite.Sprite.BindingBox;

		/*TODO:*/
		//Check if Death Animation is playing
		auto& animator = m_entity.Get<Components::Animator>();
		if (animator.GetAnimationID() == Invader::Animations::Death) {
			if (animator.End()) {
				m_entity.Kill();
			}
		}
		

	}
};

//---------------
//| OnCollision |
//---------------
////////////////////////////////////////////////////////////////////////////////
// On Collision Logic for Invader:
// -Sets the death animation if its hit by a bullet
// -Removes the entity collision component so other bullets wont get stopped
// while its dying
// -kills the bullet entity on hit as well
////////////////////////////////////////////////////////////////////////////////
void OnCollision(PA::Entity entityA, PA::Entity entityB) {
	/*TODO:*/

	//Check if Invader(EntityA) is not already in death animation:
	if (entityA.Get<Components::Animator>().GetAnimationID() !=
		Invader::Animations::Death) {

		//If EntityB is a bullet:
		if (entityB.Get<Components::Tag>().GetTag() == Bullet::Name) {
			//Set Death Animation:
			entityA.Get<Components::Animator>().Start(Invader::Animations::Death, false);
			PA::Game::AudioAssets.PlaySound(Defender::Sounds::Death);
 			entityB.Kill();
		}
		//if entityB is player:
		if (entityB.Get<Components::Tag>().GetTag() == Defender::Name) {
			auto& animator = entityB.Get<Components::Animator>(); 
			if (animator.GetAnimationID() == Defender::Animations::idle) {
				animator.Start(Defender::Animations::death, false);
				PA::Game::AudioAssets.PlaySound(Defender::Sounds::Death);
			}
		}
	}
}
}//END namespace Scripts

//--------------
//| InitAssets |
//--------------
////////////////////////////////////////////////////////////////////////////////
// Initiates all the assets for Invader entity
////////////////////////////////////////////////////////////////////////////////
void InitAssets() {
	//Load Assets:
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Invader);
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Death);
}

//----------
//| Create |
//----------
////////////////////////////////////////////////////////////////////////////////
// Creates an Invader Entity:
// -Pass a valid pointer to the scene which will create the entity into
// -Returns the created Entity
////////////////////////////////////////////////////////////////////////////////
ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene) {
	auto entity = scene->CreateEntity(Invader::Name);

	entity.Add<Components::Transform>();

	// Collider
	///////////////////
	auto& collider = entity.Add<Components::Collider>();
	collider.Tag = Invader::Name;
	collider.IsSold = false;
	collider.BindOnCollision(Scripts::OnCollision);

	// Sprite and Animations
	///////////////////
	//Add Components
	entity.Add<Components::Sprite>();
	auto& animator = entity.Add<Components::Animator>();

	//Create Animations
	PA::AnimationProperties animProps;
	animProps.SpriteSheet = SpriteSheets::Invader;
	animProps.FrameWidth = 32;
	animProps.FrameHeight = 32;
	animProps.SheetCol = 0;

	//Idle
	animProps.NumOfFrames = 1;
	animProps.SheetRow = 0;
	animProps.AnimationID = Animations::Idle;
	animProps.FrameDelay = 100;

	animator.Animations[Animations::Idle] = { animProps };

	//Death
	animProps.SpriteSheet = SpriteSheets::Death;
	animProps.NumOfFrames = 6;
	animProps.AnimationID = Animations::Death;

	animator.Animations[Animations::Death] = { animProps };
	animator.Start(Animations::Idle, true);

	//States
	///////////////////
	/*
	* not sure if states are needed for this simple game
	* might add them later
	*/
	//entity.Add<Components::StateMachine>(entity);

	//Scripts
	///////////////////
	auto& scripts = entity.Add<Components::Script>(entity);
	scripts.Add<Scripts::InvaderLogic>();

	entity.Add<Components::Parent>();

	return entity;
}

}//END namespace Entities::SpaceInvader 