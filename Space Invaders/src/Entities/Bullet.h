#pragma once
#include "ProjectAlpha.h"

namespace Entities::Bullet{
const std::string Name = "Bullet";

namespace Scripts {
struct BulletLogic;
}//END namespace Scripts 

namespace Graphics {
const std::string Bullet = "assets/graphics/bullet.png";
}//END namespace Graphics 

void InitAssets();

PA::Entity Create(PA::Scene* scene);

}//END namespace Entities::Bullet