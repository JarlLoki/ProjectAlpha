#pragma once
#include <string>
#include "SDL_mixer.h"

namespace ProjectAlpha::Audio {
using MusicData = Mix_Music;

struct Music {
	std::string Id = "";
	MusicData* Data = nullptr;

	Music() = default;
	~Music() {
		if (Data) {
			Mix_FreeMusic(Data);
			Data = nullptr;
		}
	}
};

}//END namespace ProjectAlpha::Audio 