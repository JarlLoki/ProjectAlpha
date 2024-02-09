#include "TextureManager.h"

namespace ProjectAlpha {
void TextureManager::LoadTextureFromFile(std::string filePath) {

}

Texture TextureManager::GetTextureData(TextureID id) {
	return m_loadedTextures[id];
}

}