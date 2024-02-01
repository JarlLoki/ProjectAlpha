#pragma once
#include <stdint.h>
#include <vector>

#include "Sprite.h"

namespace ProjectAlpha {

using AnimationID = uint16_t;

struct Animation {
	AnimationID ID = 0;
	std::vector<Sprite> Frames;
	uint32_t FrameDelay = 0;
};

} //END namespace ProjectAlpha