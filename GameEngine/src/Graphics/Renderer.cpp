#include "Renderer.h"

#include "SDL.h"
#include "SDL_image.h"

#include "ECS/Components/Components.h"


namespace ProjectAlpha {

Renderer::~Renderer() {
	//Unload all textures:
	for (auto& texture : m_loadedTextures) {
		if (texture.second.Data) {
			SDL_DestroyTexture(texture.second.Data);
			texture.second.Data = nullptr;
		}
	}

	SDL_DestroyRenderer(m_renderer);
}
void Renderer::SetRenderWindowTarget(Window& window) {
	m_renderer = window.CreateRenderer();
}
void Renderer::ResetDrawBuffer() {
	SDL_SetRenderDrawColor(m_renderer,
		0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
}

void Renderer::DrawBufferToWindow() {
	SDL_RenderPresent(m_renderer);
}

std::unique_ptr<RenderedText> Renderer::RenderText(const Text& text) {
	//Get the font, returns nullptr if fonttype and size doesnt exist
	TTF_Font* font = Fonts.GetFont(text.GetFontName(), text.GetFontSize());
	//If no font was found try using a default font:
	if (!font) {
		font = Fonts.GetDefaultFont();

		//Check if default font was set:
		if (font) {
			PA_LOG_WARN("Can't get font: " + text.GetFontName() +
				", " + std::to_string(text.GetFontSize()) + ". Using default " +
				"font for text: \"" + text.GetText() + "\".");
		}
		//No default font:
		else {
			PA_LOG_WARN("Can't get font: " + text.GetFontName() +
				", " + std::to_string(text.GetFontSize()) +
				". No default font set.");
		}
	}
	//TODO: Remove this if the above works
	/*
	if (!font && Fonts.GetDefaultFont()) {
		font = Fonts.GetDefaultFont();
		std::string msg = "Can't get font: " + text.GetFontName() +
			", " + std::to_string(text.GetFontSize()) + ". Using default " +
			"font for text: \"" + text.GetText() + "\".";
		//ErrorPrintOnce(msg.c_str());
		PA_LOG_WARN(msg);
	}
	//Give warning that theres no default font:
	else if (!font) {
		std::string msg = "Can't get font: " + text.GetFontName() +
			", " + std::to_string(text.GetFontSize()) +
			". No default font set.";
		//ErrorPrintOnce(msg.c_str());
		PA_LOG_WARN(msg);
	}
	*/

	//Try to render text with the font:
	if (font) {
		//Get color and convert to SDL_Color:
		Color c = text.GetColor();
		SDL_Color color = { c.r, c.g, c.b, c.a };

		//Create the surface containing the text:
		SDL_Surface* textSurface;
		textSurface = TTF_RenderText_Solid(font, text.GetText().c_str(), color);
		
		//Get the text width / height from the surface before destroying it:
		//Rect textSize = GetBindingBox(textSurface);
		//SDL_Rect sdlTextSize = { textSize.x, textSize.y, textSize.w, textSize.h };
		//int w = textSurface->w;
		//int h = textSurface->h;
		//Not used right now, instead just cropping the created surface of the text
		//in the src rect of the texture

		//Create a texture from the surface
		SDL_Texture* textTexture;
		textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

		Texture texture;
		texture.Data = textTexture;
		//texture.SrcRect = { 0,0, w, h };
		 
		//Crop the generated surface from text to exactly where the pixels are:
		//texture.SrcRect = GetBindingBox(textSurface);
		//texture.BindingBox = GetBindingBox(textSurface);

		//Cleanup the no longer needed surface
		SDL_FreeSurface(textSurface);

		return std::make_unique<RenderedText>(RenderedText(text, texture));
	} else {
		PA_LOG_ERROR("No font. Unable to render text.");
		return nullptr;
	}
}



void Renderer::LoadTextureFromFile(std::string filePath) {
	//Check if Texture is already loaded:
	if (!m_loadedTextures[filePath].Data) {
		Texture texture;
		texture.FileName = filePath;
		SDL_Surface* surface = IMG_Load(filePath.c_str());
		if (!surface) {
			//Popup
			std::string SDLError = std::string(IMG_GetError());
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error loading Image",
				SDLError.c_str(), NULL);
			PA_LOG_ERROR("Failed to load image: " + SDLError + ".");
		} else {
			Image image = { filePath, surface };
			LoadTextureFromImage(image);
		}
		SDL_FreeSurface(surface);
	}
}

void Renderer::LoadTextureFromImage(Image image) {
	Texture texture;
	texture.FileName = image.FileName;
	//Check if image data is valid:
	if (image.Data) {
		texture.Data = SDL_CreateTextureFromSurface(m_renderer, image.Data);
		if (texture.Data) {
			SDL_QueryTexture(texture.Data, NULL, NULL, &texture.Width, 
				                                       &texture.Height);
		} else {
			PA_LOG_ERROR("Failed to create texture. " + 
				std::string(SDL_GetError()));
		}
	}
	m_loadedTextures[texture.FileName] = texture;
}

void Renderer::LoadAllTexturesFromImages(ImageManager images) {
	auto& loadedImages = images.GetLoadedImages();
	for (auto image : loadedImages) {
		LoadTextureFromImage(image.second);
	}
}

void Renderer::UnloadTexture(std::string filePath) {
	if (m_loadedTextures[filePath].Data) {
		SDL_DestroyTexture(m_loadedTextures[filePath].Data);
		m_loadedTextures[filePath].Data = nullptr;
	}
}

//
//Draw Functions
/////////////////////////////////

void Renderer::DrawTexture(const Texture& texture, Vector2D pos, float scale) {
	if (!texture.Data) {
		SDL_Texture* sdlTexture = texture.Data;

		SDL_Rect sdlDst = { static_cast<int>(pos.x * scale),
							static_cast<int>(pos.y * scale),
							static_cast<int>(texture.Width * scale),
							static_cast<int>(texture.Height * scale) };

		SDL_RenderCopy(m_renderer, sdlTexture, nullptr, &sdlDst);
	}
}

void Renderer::DrawTexture(const Texture& texture, Rect src, Vector2D pos, float scale) {
	if (!texture.Data) {
		SDL_Texture* sdlTexture = texture.Data;

		SDL_Rect sdlSrc = { src.x, src.y, src.w, src.h };

		SDL_Rect sdlDst = { static_cast<int>(pos.x * scale),
							static_cast<int>(pos.y * scale),
							static_cast<int>(src.w * scale),
							static_cast<int>(src.h * scale) };

		SDL_RenderCopy(m_renderer, sdlTexture, &sdlSrc, &sdlDst);
	}
}

void Renderer::DrawSprite(const SpriteComponent& sprite, 
	                      const TransformComponent& transform,
						  float scale) {

	Texture texture = GetTexture(sprite.Sprite.SpriteSheet);
	Rect src = sprite.Sprite.SrcRect;
	Vector2D pos = transform.Position;

	if (!texture.Data) {
		DrawTexture(texture, src, pos, scale);
	}
	else {
		//Draw a default texture?
	}
}

void Renderer::DrawRect(Rect rect, Color color, bool fill, float scale) {
	//rect.w *= scale;
	//rect.h *= scale;
	rect *= scale;
	//SDL_Rect dst = rect.ToSDL_Rect();
	SDL_Rect dst = { rect.x, rect.y, rect.w, rect.h };


	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	if (fill)
		SDL_RenderFillRect(m_renderer, &dst);
	else
		SDL_RenderDrawRect(m_renderer, &dst);

}

void Renderer::DrawLine(Vector2D src, Vector2D dst, Color color, float scale) {
	src *= scale;
	Point pSrc = src.ToPoint();
	
	dst *= scale;
	Point pDst = dst.ToPoint();
	

	SDL_SetRenderDrawColor(m_renderer, color.r, color.b, color.g, color.a);
	SDL_RenderDrawLine(m_renderer, pSrc.x, pSrc.y, pDst.x, pDst.y);

}


Rect Renderer::GetViewPort() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return Rect(viewport.x, viewport.y, viewport.w, viewport.h);
}

int Renderer::GetViewPortWidth() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return viewport.w;
}

int Renderer::GetViewPortHeight() const {
	SDL_Rect viewport;
	SDL_RenderGetViewport(m_renderer, &viewport);
	return viewport.h;

}

Texture& Renderer::GetTexture(std::string filePath) {
	if (!m_loadedTextures[filePath].Data) {
		PA_LOG_WARN("Texture was not preloaded. File: " + filePath);
		LoadTextureFromFile(filePath);
	}
	return m_loadedTextures[filePath];
}









}//End ProjectAlpha namespace
