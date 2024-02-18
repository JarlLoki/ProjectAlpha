#include "SDL.h"
#include "SDL_image.h"

#include "Log.h"
#include "ImageManager.h"

namespace ProjectAlpha {

ImageManager::~ImageManager() {
	//unload Images
	for (auto& image : m_loadedImages) {
		if (image.second.Data) {
			SDL_FreeSurface(image.second.Data);
			image.second.Data = nullptr;
		}		
	}
}

void ImageManager::LoadImageFromFile(std::string filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	if (!surface) {
		//Popup
		std::string SDLError = std::string(IMG_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error loading Image",
			SDLError.c_str(), NULL);
		PA_LOG_ERROR("Failed to load image: " + SDLError + ".");
		surface = nullptr;
	} 
	m_loadedImages[filePath] = { filePath, surface };
}

void ImageManager::UnloadImage(std::string filePath) {
	if (m_loadedImages[filePath].Data) {
		SDL_FreeSurface(m_loadedImages[filePath].Data);
		m_loadedImages[filePath].Data = nullptr;
	}
}

Image ImageManager::GetImage(std::string filePath) {
	if (!m_loadedImages[filePath].Data) {
		LoadImageFromFile(filePath);
	}
	return m_loadedImages[filePath];
}

//const auto& ImageManager::GetLoadedImages() {
//	return m_loadedImages;
//}

const std::unordered_map<std::string, Image>& ImageManager::GetLoadedImages() const {
	return m_loadedImages;
}

}//END namespace ProjectAlpha
