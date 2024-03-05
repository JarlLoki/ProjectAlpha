#pragma once
#include <string>
#include "SDL_mixer.h"

namespace ProjectAlpha::Audio {
using SoundData = Mix_Chunk;

struct Sound {
	std::string Id = "";
	SoundData* Data = nullptr;

	Sound() = default;
	~Sound() { 
		if (Data) {
			Mix_FreeChunk(Data);
			Data = nullptr;
		}
	}
};

}//END namespace ProjectAlpha::Audio 