#pragma once
#include <string>
#include "BasicDataContainers/Rect.h"

namespace ProjectAlpha {

struct Sprite {
	Sprite() {
		SpriteSheetPath = "";
		SrcRect = { 0,0,0,0 };
		BindingBox = { 0,0,0,0 };
	}
	std::string  SpriteSheetPath;
	Rect SrcRect;
	Rect BindingBox;
};

}