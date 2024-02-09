#include "Text.h"

namespace ProjectAlpha {

// Text
////////////////////////////
Text::Text(std::string font, int size, std::string text, Color c) :
	m_fontName(font), m_fontSize(size), m_text(text), m_color(c) {
}

std::string Text::GetText() const { return m_text; }
std::string Text::GetFontName() const { return m_fontName; }
int Text::GetFontSize() const { return m_fontSize; }
Color Text::GetColor() const { return m_color; }




// RenderedText
////////////////////////////
RenderedText::RenderedText(Text text, Texture texture)
	: Text(text), m_texture(texture) {}

RenderedText::~RenderedText() {
	if (!m_texture.Data) {
		SDL_DestroyTexture(m_texture.Data);
		m_texture.Data = nullptr;
	}
}

Texture RenderedText::GetTexture() const { return m_texture; }
int RenderedText::GetWdith() const { return m_texture.Width; }
int RenderedText::GetHeight() const { return m_texture.Height; }

bool operator == (const RenderedText& lvalue, const Text& rvalue) {
	if (lvalue.GetFontName() == rvalue.GetFontName() &&
		lvalue.GetFontSize() == rvalue.GetFontSize() &&
		lvalue.GetText() == rvalue.GetText() &&
		lvalue.GetColor() == rvalue.GetColor()) {
		return true;
	}
	return false;
}

}//END namespace Project Alpha
