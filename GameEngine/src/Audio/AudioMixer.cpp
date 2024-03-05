#include <string>
#include "AudioMixer.h"

#include "Log.h"

namespace ProjectAlpha::Audio {

AudioMixer::AudioMixer() {
	//Init SDL_Mixer
	int result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	//if (result != 0)
		//ErrorPopup("ERROR INITILIZING MIXER:", Mix_GetError());

}

AudioMixer::~AudioMixer() {
	//Close and stop any audio:
	Mix_CloseAudio();

	//No need to delete loaded sounds/music because they are stored as 
	//shared_ptr and will be delete after they go out of scope completely

	//Cleanup mixer
	Mix_Quit();
}

//-------------
//| LoadSound |
//-------------
////////////////////////////////////////////////////////////////////////////////
// Loads sounds from a file name and stores it in memory using an unordered map
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::LoadSound(std::string file) {
	//Check if Sound is already Loaded:
	if (!m_loadedSounds[file] || m_loadedSounds[file]->Data) {		
		m_loadedSounds[file] = std::make_unique<Sound>(Sound());
		m_loadedSounds[file]->Id = file;
		m_loadedSounds[file]->Data = Mix_LoadWAV(file.c_str());
		if (!m_loadedSounds[file]->Data) {
			PA_LOG_ERROR("Error Loading Sound: " + std::string(Mix_GetError()));
		}
	}
	/*
		if (!m_loadedSounds[file]->Data) {
		m_loadedSounds[file]->Id = file;
		m_loadedSounds[file]->Data = Mix_LoadWAV(file.c_str());
		if (!m_loadedSounds[file]->Data) {
			PA_LOG_ERROR("Error Loading Sound: " + std::string(Mix_GetError()));
		}
	}
	*/
}

//---------------
//| UnloadSound |
//---------------
////////////////////////////////////////////////////////////////////////////////
// Deletes the sound with the given file path from memory
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::UnloadSound(std::string file) {
	if (m_loadedSounds[file]->Data) {
		m_loadedSounds[file].reset();
	}
}

//-------------------
//| UnloadAllSounds |
//-------------------
////////////////////////////////////////////////////////////////////////////////
// Deletes all sounds that were loaded into memory
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::UnloadAllSounds() {
	for (auto& sound : m_loadedSounds) {
		sound.second.reset();
	}
}

//-------------
//| PlaySound |
//-------------
////////////////////////////////////////////////////////////////////////////////
// Plays the sound from memory, if its not already loaded it will attempt to load
// the sound first
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::PlaySound(std::string file) {
	if (!m_loadedSounds[file] || m_loadedSounds[file]->Data) {
		LoadSound(file);
	} 
	if (m_loadedSounds[file]->Data) {
		Mix_PlayChannel(-1, m_loadedSounds[file]->Data, 0);
	} else {
		PA_LOG_ERROR("Sound data missing, unable to play: " + file);
	}
}

//-------------
//| LoadMusic |
//-------------
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::LoadMusic(std::string file) {
}

//---------------
//| UnLoadMusic |
//---------------
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::UnloadMusic(std::string file) {
}

//------------------
//| UnLoadAllMusic |
//------------------
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::UnloadAllMusic() {
}

//-------------
//| PlayMusic |
//-------------
////////////////////////////////////////////////////////////////////////////////
// 
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::PlayMusic(std::string file) {
}

//-------------
//| UnloadAll |
//-------------
////////////////////////////////////////////////////////////////////////////////
// Unloads all Sounds and Music that were loaded in memory
////////////////////////////////////////////////////////////////////////////////
void AudioMixer::UnloadAll() {
	UnloadAllSounds();
	UnloadAllMusic();
}

}//END namespace ProjectAlpha::Audio
