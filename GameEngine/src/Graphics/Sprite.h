#pragma once
#include <string>
#include "BasicDataContainers/Rect.h"

namespace ProjectAlpha {

struct Sprite {
	std::string SpriteSheet = "";
	Rect SrcRect = { 0,0,0,0 };
	Rect BindingBox = { 0,0,0,0 };
};

}