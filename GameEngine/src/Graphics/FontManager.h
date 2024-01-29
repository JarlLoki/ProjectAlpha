#pragma once
#include <string>
#include <map>

#include "SDL_ttf.h"
#include "../Log.h"
//#include "error.h"


namespace ProjectAlpha {

class FontManager {
public: //Interface
	FontManager();
	~FontManager();

	bool Init() {
		//Init Text Rendering
		if (TTF_Init() < 0) {
			//ErrorPopup("SDL Font TTF Init Failure: ", TTF_GetError());
			PA_LOG_ERROR(TTF_GetError());
			return false;
		}
		return true;
	}

	//Must end with '/'
	void SetFontDir(std::string path);

	//Name should not include .ttf extension
	TTF_Font* LoadFont(std::string name, int size);

	//
	TTF_Font* GetFont(std::string name, int size);

	//
	void SetDefaultFont(std::string name, int size);
	TTF_Font* GetDefaultFont();

	void UnloadAllFonts();
private:
	void* operator =(void*) {}; // prevent assignment

private: //members
	TTF_Font* m_defaultFont;
	std::map<std::string, std::map<int, TTF_Font*>> m_loadedFonts;
	std::map<std::string, std::map<int, bool>> m_triedLoading;
	std::string m_path;
};

}//END namespace ProjectAlpha