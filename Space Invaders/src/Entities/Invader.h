#pragma once
#include "ProjectAlpha.h"
namespace Entities::Invader {
const std::string Name = "Invader";

namespace Scripts {
struct InvaderLogic;

void OnCollision(PA::Entity entityA, PA::Entity entityB);

}//END namespace Scripts

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
}//END namespace SpriteSheets

void InitAssets();

ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene);

}//END namespace Entities::Invader