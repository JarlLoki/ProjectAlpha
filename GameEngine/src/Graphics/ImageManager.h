#pragma once
#include <unordered_map>
#include "Image.h"

namespace ProjectAlpha {

class ImageManager {
public:
	ImageManager() = default;
	~ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager* operator=(const ImageManager&) = delete;

	void LoadImageFromFile(std::string filePath);
	void UnloadImage(std::string filePath);
	Image GetImage(std::string filePath);

	const std::unordered_map<std::string, Image>& GetLoadedImages();
	//const auto& GetLoadedImages();

private:
	std::unordered_map<std::string, Image> m_loadedImages;

};

} //END namespace ProjectAlpha 