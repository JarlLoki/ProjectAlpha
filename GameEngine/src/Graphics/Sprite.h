#pragma once
#include <string>
#include "BasicDataContainers/Rect.h"

namespace ProjectAlpha {

struct Sprite {
	Sprite() {
		SpriteSheet = "";
		SrcRect = { 0,0,0,0 };
		BindingBox = { 0,0,0,0 };
	}
	std::string  SpriteSheet;
	Rect SrcRect;
	Rect BindingBox;
};

}