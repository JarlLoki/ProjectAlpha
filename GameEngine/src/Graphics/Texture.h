#pragma once
#include <string>
#include "SDL.h"
#include "BasicDataContainers/Rect.h"

namespace ProjectAlpha {

using TextureID = uint32_t;

struct Texture {
	std::string FileName;
	SDL_Texture* Data = nullptr;
	int Width = 0;
	int Height = 0;
	//Rect SrcRect;
	//Rect BindingBox;

};


}