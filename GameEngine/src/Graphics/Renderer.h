#pragma once

#include <map>
#include <string>
#include <memory>

#include "BasicDataContainers/Vector2D.h"
#include "BasicDataContainers/Color.h"
#include "BasicDataContainers/Rect.h"
#include "BasicDataContainers/Point.h"

#include "Sprite.h"
#include "Texture.h"
#include "Window.h"
#include "../Log.h"
#include "Text.h"
#include "FontManager.h"

namespace ProjectAlpha {

class Renderer {
public:
	Renderer();
	~Renderer();

	//

	void SetRenderWindowTarget(Window& window);
	//

	void ResetDrawBuffer();
	void DrawBufferToWindow();

	//Render Functions
	// RenderText(const Text& text);

	std::unique_ptr<RenderedText> RenderText(const Text& text);

	//Draw Functions

	void DrawTexture(const Texture& texture, Vector2D position, float scale);
	void DrawSprite(const Sprite& sprite, Rect dst, float scale);

	//Basic Draw Functions

	void DrawRect(Rect rect, Color color, bool fill, float scale);
	void DrawLine(Vector2D src, Vector2D dst, Color color, float scale);
	
	//Viewport

	Rect GetViewPort() const;
	int GetViewPortWidth() const;
	int GetViewPortHeight() const;

	//	

	SDL_Renderer* Get() { return m_renderer; }
	FontManager Fonts;
private:
	Texture& GetTexture(const Sprite& sprite);
	Texture& LoadTextureFromFile(std::string filePath);
	


private:
	SDL_Renderer* m_renderer;

	std::map<std::string, Texture> m_loadedTextures;

};

//Get Pixel Functions:
////////////////////

/*
* Returns a uint32 id that represents a raw SDL pixel
*/
Uint32 GetRawPixel(SDL_Surface* surface, int x, int y);

/*
* Returns an SDL_Color that represents an RGBA pixel
* at the given x,y coordinates of the provided surface
*/
SDL_Color GetRGBAPixel(SDL_Surface* surface, int x, int y);
////////////////////



//GetBindingBox
////////////////////
/*
* Returns a rect around the non-transparent pixels in a surface.
*/
Rect GetBindingBox(SDL_Surface* surface);

/*
* Uses the provided rect to crop the surface and then
* Returns a rect around the non-transparent pixels
*/
Rect GetBindingBox(SDL_Surface* surface, Rect rect);
////////////////////

inline void SDL_CropSurface(SDL_Surface* surface, SDL_Rect rect) {
	SDL_Surface* clippedSurface = SDL_CreateRGBSurface(
		surface->flags,
		rect.w, rect.h,
		surface->format->BitsPerPixel,
		surface->format->Rmask,
		surface->format->Gmask,
		surface->format->Bmask,
		surface->format->Amask);

	SDL_BlitSurface(surface, &rect, clippedSurface, NULL);

	SDL_Surface* tempSurface = surface;
	surface = clippedSurface;
	SDL_FreeSurface(tempSurface);
}




}