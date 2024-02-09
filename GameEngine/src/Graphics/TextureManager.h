#pragma once
#include <unordered_map>

#include "SDL.h"

#include "Texture.h"

namespace ProjectAlpha {

class TextureManager {
public:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager* operator=(const TextureManager&) = delete;

	void LoadTextureFromFile(std::string filePath);

	Texture GetTextureData(TextureID id);
	Texture GetTextureData(std::string spriteSheet) { return {}; }


private:
	//Container for Texture?
	std::unordered_map<TextureID, Texture> m_loadedTextures;

};

}//END namespace ProjectAlpha