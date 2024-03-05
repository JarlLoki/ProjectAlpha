#pragma once
#include <unordered_map>
#include <memory>

#include "Sound.h"
#include "Music.h"

namespace ProjectAlpha::Audio {

class AudioMixer {
public://Interface
	AudioMixer();
	~AudioMixer();
	AudioMixer(const AudioMixer&) = delete;
	AudioMixer* operator=(const AudioMixer&) = delete;

	void LoadSound(std::string file);
	void UnloadSound(std::string file);
	void UnloadAllSounds();
	void PlaySound(std::string file);

	void LoadMusic(std::string file);
	void UnloadMusic(std::string file);
	void UnloadAllMusic();
	void PlayMusic(std::string file);

	void UnloadAll();

private://Members & Functions
	std::unordered_map<std::string, std::unique_ptr<Sound>> m_loadedSounds;
	std::unordered_map<std::string, std::unique_ptr<Music>> m_loadedMusic;
};

}//END namespace ProjectAlpha::Audio 