#pragma once
#include <string>

#include "SDL.h"

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
	RenderedText(Text text, SDL_Texture* texture, int w, int h);

	SDL_Texture* GetTexture() const;
	int GetWdith() const;
	int GetHeight() const;

private://Members
	SDL_Texture* m_textTexture;
	int m_width;
	int m_height;

};

bool operator == (const RenderedText& lvalue, const Text& rvalue);


RenderedText* RenderText(SDL_Renderer*, const Text& text);

} //END namespace ProjectAlpha