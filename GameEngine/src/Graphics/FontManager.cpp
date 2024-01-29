#include "FontManager.h"

namespace ProjectAlpha {

FontManager::FontManager() {

	Init();

	m_defaultFont = nullptr;
	m_path = "";
}

FontManager::~FontManager() {
	//Close all the loaded fonts:
	for (auto& fontName : m_loadedFonts) {
		for (auto& fontSize : fontName.second) {
			TTF_CloseFont(fontSize.second);
		}
	}
	TTF_Quit();

}
void FontManager::UnloadAllFonts() {

}

void FontManager::SetFontDir(std::string path) { m_path = path; }

TTF_Font* FontManager::LoadFont(std::string name, int size) {
	std::string fontPath = m_path + name + ".ttf";
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), size);
	if (!font) {
		std::string errorMsg = "Failed to load font: " + name + ", " +
			std::to_string(size) + ". Reason: " + TTF_GetError();
		//ErrorPrintOnce(errorMsg.c_str());
		PA_LOG_ERROR(errorMsg);
	}
	m_triedLoading[name][size] = true;
	m_loadedFonts[name][size] = font;
	return font;
}

TTF_Font* FontManager::GetFont(std::string name, int size) {
	TTF_Font* font = m_loadedFonts[name][size];
	//If No font found:
	//Try loading it if it hasnt already been loaded:
	if (!font && !m_triedLoading[name][size]) {
		font = this->LoadFont(name, size);
	}
	return font;
}

void FontManager::SetDefaultFont(std::string name, int size) {
	TTF_Font* font = GetFont(name, size);
	//If cant get a default font then give a warning:
	if (!font) {
		std::string msg = "Can't set the default font: " +
			name + ", " + std::to_string(size) + ". No default font set.";
		//ErrorPrintOnce(msg.c_str());
		PA_LOG_WARN(msg);
	}
	m_defaultFont = font;
}

TTF_Font* FontManager::GetDefaultFont() {
	return m_defaultFont;
}

}//END namespace ProjectAlpha