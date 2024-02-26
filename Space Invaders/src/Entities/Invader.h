#pragma once
#include "ProjectAlpha.h"
namespace Entities::SpaceInvader {

namespace Animations {
enum {
	Idle,
	Death
};
}//END namespace Animations

namespace Sounds {
const std::string Death = "assets/sounds/explosion.wav";
const std::string Move_Tick = "assets/sounds/doo_tick.wav";
const std::string Move_Tock = "assets/sounds/doo_tock.wav";
}//END namespace Sound 

namespace SpriteSheets {
const std::string Invader = "assets/graphics/invader.png";
const std::string Death = "assets/graphics/invader_death.png";
}


ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene) {
	auto entity = scene->CreateEntity("Invader");
	entity.Add<Components::Transform>();
	entity.Add<Components::Physics>();
	entity.Add<Components::Collider>();
	entity.Add<Components::Sprite>();
	entity.Add<Components::Animator>();
	entity.Add<Components::StateMachine>();
	entity.Add<Components::Script>();
	entity.Add<Components::Parent>();

	return entity;
}

}//END namespace Entities::Invader