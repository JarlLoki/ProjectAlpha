#pragma once
#include "ProjectAlpha.h"

namespace Entities::Defender {
const std::string Name = "Defender";

namespace Scripts {
struct DefenderLogic;
}//END namespace Scripts

namespace Sounds {
const std::string Shooting = "assets/sounds/pew_low.wav";
const std::string Death = "assets/sounds/explosion.wav";
}//END namespace Sounds 

namespace SpriteSheets {
const std::string Idle = "assets/graphics/defender.png";
const std::string Death = "assets/graphics/defender_death.png";
const std::string Dead = "assets/graphics/defender_dead.png";
}//END namespace SpriteSheets

namespace Animations {
enum {	
	idle,
	death,
	dead
};
}//END namespace Animations

namespace States {
enum {
	alive,
	dead
};
}//END namespace States 

void InitAssets();

ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene);

}//END namespace Entities::Defender