#pragma once
#include <string>
#include "SDL.h"

namespace ProjectAlpha {

struct Image {
	std::string FileName = "";
	SDL_Surface* Data = nullptr;
};

} //ENDnamespace ProjectAlpha