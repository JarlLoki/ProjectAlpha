#pragma once
#include "ProjectAlpha.h"
namespace Entities::LevelBackground {

namespace SpriteSheets {
const std::string Rails = "assets/graphics/defender_rails.png";
const std::string Space = "assets/graphics/space_500x500.png";
const std::string Moon = "assets/graphics/level_base.png";
}

void InitAssets() {
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Rails);
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Space);
	PA::Game::ImageAssets.LoadImageFromFile(SpriteSheets::Moon);
}

void Create(PA::Scene* scene) {
	//Create Space background:
	{
		auto space = scene->CreateEntity("space");
		space.Add<Components::Transform>(0, 0);
		auto& sprite = space.Add<Components::Sprite>();
		sprite.Sprite = { SpriteSheets::Space, {0,0,500,500} };
		sprite.DrawLayer = 10;

	}

	//Create Rails:
	int iX_max = (500 / 32) +1;
	
	for (int iX = 0; iX < iX_max; iX++) {
		auto rail = scene->CreateEntity("rail");
		rail.Add<Components::Transform>(iX*32, 500);
		auto& sprite = rail.Add<Components::Sprite>();
		sprite.Sprite = { SpriteSheets::Rails, {0,0,32,32} };
		sprite.DrawLayer = 10;
	}

	//Create moon base:
	{
		auto moon = scene->CreateEntity("moon");
		moon.Add<Components::Transform>(-132, 532);
		auto& sprite = moon.Add<Components::Sprite>();
		sprite.Sprite = { SpriteSheets::Moon, {0,0, 1000, 64} };
		sprite.DrawLayer = 10;
	}


}

}