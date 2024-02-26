#pragma once
#include "ProjectAlpha.h"

namespace Entities::Defender {

namespace Animations {
enum {	
	idle,
	death
};
}

namespace States {
enum {
	alive,
	dead
};
}

ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene);

}