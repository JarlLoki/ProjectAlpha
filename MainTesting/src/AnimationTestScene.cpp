#include "AnimationTestScene.h"
#include "TestGame.h"
#include "GameScripts.h"
#include "Adventure.h"

AnimationTest::AnimationTest(TestGame* Game) : Scene("AnimTest"){
	ProjectAlpha::Entity player =  CreateEntity("player");
	Adventure::Create(player);

	ProjectAlpha::Entity camera = CreateEntity("Camera");
	auto& camc = camera.Add<Components::Camera>();
	camc.ZoomScale = 3;
	auto& tran = camera.Add<Components::Transform>();
	tran.Position = { 0,0 };

	/*
	ProjectAlpha::Entity spriteTest = CreateEntity("Sprite_test");
	auto& tc = spriteTest.Add<Components::Transform>();
	tc.Position = { 0,0 };
	auto& sc = spriteTest.Add<ProjectAlpha::SpriteComponent>();
	sc.Sprite = { "assets/images/adventurer_sprite_sheet_v1.1.png", 
		           {0,0,2000,2000}, {0,0,0,0} };
				   */
	Game->GetRenderer().LoadAllTexturesFromImages(Game->ImageAssets);
}
