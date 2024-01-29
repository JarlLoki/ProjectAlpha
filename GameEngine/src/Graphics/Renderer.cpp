

#include "Renderer.h"


namespace ProjectAlpha {
Renderer::Renderer() {

}
Renderer::~Renderer() {
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
		texture.data = textTexture;
		//texture.SrcRect = { 0,0, w, h };
		// 
		//Crop the generated surface from text to exactly where the pixels are:
		texture.SrcRect = GetBindingBox(textSurface);
		//texture.BindingBox = GetBindingBox(textSurface);

		//Cleanup the no longer needed surface
		SDL_FreeSurface(textSurface);

		return std::make_unique<RenderedText>(RenderedText(text, texture));
	} else {
		PA_LOG_ERROR("No font. Unable to render text.");
		return nullptr;
	}
}


//
//Draw Functions
/////////////////////////////////
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



void Renderer::DrawTexture(const Texture &texture, Vector2D position, float scale)  {

	SDL_Texture* sdlTexture = texture.data;

	SDL_Rect sdlSrc = { texture.SrcRect.x, texture.SrcRect.y,
					    texture.SrcRect.w, texture.SrcRect.h };
	

	SDL_Rect sdlDst = { static_cast<int>(position.x * scale),
						static_cast<int>(position.y * scale),
						static_cast<int>(texture.SrcRect.w * scale),
						static_cast<int>(texture.SrcRect.h * scale) };

	SDL_RenderCopy(m_renderer, sdlTexture, &sdlSrc, &sdlDst);
}

void Renderer::DrawSprite(const Sprite &sprite, Rect dst, float scale) {
	Texture& texture = GetTexture(sprite);

	//DrawTexture(texture, dst, scale);
}




Texture& Renderer::GetTexture(const Sprite& sprite) {
	Texture& texture = m_loadedTextures[sprite.SpriteSheetPath];

	if (!texture.data) {
		PA_LOG_WARN("Texture " + sprite.SpriteSheetPath + " not preloaded. Attempting to load texture.");
		//No texture data found, try loading it from file path:
		texture = LoadTextureFromFile(sprite.SpriteSheetPath);
	}
	return texture;
}

Texture& Renderer::LoadTextureFromFile(std::string filePath) {
	Texture texture;


	return texture;
}




//Get Pixel Functions:
////////////////////

/*
* Returns a uint32 id that represents a raw SDL pixel
*/
Uint32 GetRawPixel(SDL_Surface* surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32*)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

/*
* Returns an SDL_Color that represents an RGBA pixel
* at the given x,y coordinates of the provided surface
*/
SDL_Color GetRGBAPixel(SDL_Surface* surface, int x, int y) {
	Uint32 raw = GetRawPixel(surface, x, y);
	SDL_Color pixel;
	SDL_GetRGBA(raw, surface->format, &pixel.r, &pixel.g, &pixel.b, &pixel.a);
	return pixel;
}
////////////////////



//GetBindingBox
////////////////////
/*
* Returns a rect around the non-transparent pixels in a surface.
*/
Rect GetBindingBox(SDL_Surface* surface) {
	Rect box;
	bool yFound = false;
	box.x = surface->w - 1;
	int rightX = 0; //furest right non-transparent pixel x-axis
	int bottomY = 0;
	bool bottomYFound = false;

	Uint32 colorkey;
	SDL_GetColorKey(surface, &colorkey);


	/*
	Checking each pixel and if it isnt transparent then we are updating
	the binding box size:

	A transparent pixel can either be the surface colorkey or
	pixel alpha set to 0
	*/
	for (int y = 0; y < surface->h; y++) {
		bool xFound = false;
		for (int x = 0; x < surface->w; x++) {
			if (!(GetRawPixel(surface, x, y) == colorkey ||
				GetRGBAPixel(surface, x, y).a == 0)) {

				if (xFound == false) xFound = true;
				if (yFound == false) {
					yFound = true;
					box.y = y;
				}

				if (x < box.x)
					box.x = x;
				if (x > rightX) {
					rightX = x;
				}
			}
		}
		if (xFound) bottomY = y;
	}
	box.w = rightX - box.x + 1;
	box.h = bottomY - box.y + 1;

	return box;
}

/*
* Uses the provided rect to crop the surface and then
* Returns a rect around the non-transparent pixels
*/
Rect GetBindingBox(SDL_Surface* surface, Rect rect) {
	SDL_Rect src;
	src.x = rect.x;
	src.y = rect.y;
	src.w = rect.w;
	src.h = rect.h;

	SDL_Surface* spriteSurface;
	spriteSurface = SDL_CreateRGBSurface(0, src.w, src.h, 32,
		surface->format->Rmask,
		surface->format->Gmask,
		surface->format->Bmask,
		surface->format->Amask);
	SDL_BlitSurface(surface, &src, spriteSurface, NULL);

	Rect box = GetBindingBox(spriteSurface);
	SDL_FreeSurface(spriteSurface);

	return box;
}
////////////////////



}//End ProjectAlpha namespace
