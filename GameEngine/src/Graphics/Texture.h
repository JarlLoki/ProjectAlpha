#pragma once
#include "SDL.h"
#include "BasicDataContainers/Rect.h"

namespace ProjectAlpha {

struct Texture {
	Texture() {
		data = nullptr;
		SrcRect = { 0,0,0,0 };
		BindingBox = { 0,0,0,0 };
	}
	SDL_Texture* data;
	Rect SrcRect;
	Rect BindingBox;

};


}