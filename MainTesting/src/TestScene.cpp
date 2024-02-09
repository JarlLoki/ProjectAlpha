#include "TestScene.h"

#include "TestGame.h"
#include "GameScripts.h"


/*/
struct AnimationProperties {
	unsigned int AnimationID = 0;
	std::string SpriteSheet = "";
	int NumOfFrames = 0;
	int FrameWidth = 0;
	int FrameHeight = 0;
	int SheetRow = 0;
	int SheetCol = 0;
	int FrameDelay = 0;
};
*/

namespace Hero::Animations {
enum Animations {
	Idle,
	IdleDown,
	IdleLeft,
	IdleUp,
	IdleRight,
	Run,
	RunDown,
	RunLeft,
	RunUp,
	RunRight,
	Attack,
	AttackDown,
	AttackLeft,
	AttackUp,
	AttackRight
};
}

namespace Hero {

namespace PA = ProjectAlpha;

void CreateMyAnimations(TestGame* game) {

	PA::Entity otherHero;
	auto& animator = otherHero.Get<PA::AnimatorComponent>();

	PA::AnimationProperties animProps;
	animProps.SpriteSheet = "assets/myotherhero_spritesheet.png";
	animProps.FrameWidth = 32;
	animProps.FrameHeight = 32;
	animProps.SheetCol = 0;

	//Idle
	animProps.AnimationID = Animations::IdleDown;
	animProps.SheetRow = 0;
	animProps.NumOfFrames = 3;
	animProps.FrameDelay = 300;
	for (int i = 0; i < 4; i++) {
		animProps.AnimationID += i;
		animProps.SheetRow += i;
		animator.Animations[animProps.AnimationID] = PA::Animation(animProps);
	}
	//Run
	animProps.AnimationID = Animations::RunDown;
	animProps.SheetRow = 4;
	animProps.NumOfFrames = 6;
	animProps.FrameDelay = 200;
	for (int i = 0; i < 4; i++) {
		animProps.AnimationID += i;
		animProps.SheetRow += i;
		animator.Animations[animProps.AnimationID] = PA::Animation(animProps);
	}

	//Run
	animProps.AnimationID = Animations::AttackDown;
	animProps.SheetRow = 8;
	animProps.NumOfFrames = 5;
	animProps.FrameDelay = 150;
	for (int i = 0; i < 4; i++) {
		animProps.AnimationID += i;
		animProps.SheetRow += i;
		animator.Animations[animProps.AnimationID] = PA::Animation(animProps);
	}


	

	{
		std::string myheroSheet = "assets/myhero_spritesheet.png";

		PA::Entity hero;

		auto& animator = hero.Get<PA::AnimatorComponent>();

		//Idle Animation

		auto frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 0, 0);
		animator.Animations[Animations::IdleDown] = { Animations::IdleDown, frames, 200 };

		frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 1, 0);
		animator.Animations[Animations::Run] = { Animations::Run, frames, 200 };

		frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 2, 0);
		animator.Animations[Animations::Attack] = { Animations::Attack, frames, 200 };


		frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 0, 0);
		PA::Animation idle = { Animations::Idle, frames, 200 };


		PA::Animation run = { Animations::Run,
							  PA::CreateFrames(myheroSheet, 50, 50, 5, 1, 0),
							  200 };

		frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 3, 0);
		PA::Animation attack = { Animations::Attack, frames, 150 };


		frames = PA::CreateFrames(myheroSheet, 50, 50, 5, 0, 0);
		animator.Animations[Animations::Idle] = { Animations::Idle, frames, 200 };

	}
}

void MakeMyEntity(TestGame* game) {

}
}

TestScene::TestScene(TestGame* game) : Scene("Test") {

	//Load Resources
	//game->Textures.LoadTextureFromFile("assets/MyTexture.png");
	game->GetRenderer().LoadTextureFromFile("assets/rando/my_texture.png");


	//Make BLue Square
	{
		auto player = CreateEntity("player");
		auto& transform = player.Add<Components::Transform>();
		transform.Position = { 100.0f, 100.0f };
		auto& square = player.Add<ProjectAlpha::SquareComponent>();
		square.color = { 0,255,255, 0 };
		square.height = 100;
		square.width = 100;

		auto& physics = player.Add<ProjectAlpha::PhysicsComponent>();
		physics.Speed = 1;

		auto& cameraComp = player.Add<ProjectAlpha::CameraComponent>();
		cameraComp.ZoomScale = 4;
		cameraComp.offSet = { square.width / 2, square.height / 2};
		cameraComp.Center = true;
		auto& scripts = player.Add<ProjectAlpha::ScriptComponent>(player);
		scripts.Add<WSADControlScript>();
		scripts.Add<CameraZoomScript>();

		auto& collider = player.Add<ProjectAlpha::ColliderComponent>();
		collider.rect = { 0, 0, square.width, square.height };

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
		text.RenderedText = game->GetRenderer().RenderText({ text.FontName, text.FontSize,
													  text.Text, text.Color });


		square.width = text.RenderedText->GetWdith();
		square.height = text.RenderedText->GetHeight();

		auto& collider = boo.Add<ProjectAlpha::ColliderComponent>();
		collider.rect = { 0, 0, square.width, square.height };

		auto& physics = boo.Add <ProjectAlpha::PhysicsComponent>();
		physics.IsMovable = false;

	}


}