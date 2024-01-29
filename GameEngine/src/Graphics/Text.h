#pragma once
#include <string>
#include <memory>

#include "SDL.h"

#include "Texture.h"
#include "BasicDataContainers/Color.h"

namespace ProjectAlpha {

class Text {
public:
	Text(std::string font, int size, std::string text, Color c);


	std::string GetText() const;
	std::string GetFontName() const;
	int GetFontSize() const;
	Color GetColor() const;

private: //Members
	std::string m_text;
	std::string m_fontName;
	int m_fontSize;
	Color m_color;
};

class RenderedText : public Text {
public: //Interface
	RenderedText(Text text, Texture texture);
	//RenderedText(Text text, SDL_Texture* texture, int w, int h);
	~RenderedText();
	
	Texture GetTexture() const;
	//SDL_Texture* GetTexture() const;
	int GetWdith() const;
	int GetHeight() const;

private://Members
	Texture m_texture;
};

bool operator == (const RenderedText& lvalue, const Text& rvalue);



} //END namespace ProjectAlpha