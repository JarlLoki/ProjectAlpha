#pragma once
#include <string>
#include "SDL.h"

#include "BasicDataContainers/Point.h"
#include "BasicDataContainers/Rect.h"
#include "BasicDataContainers/Color.h"
#include "BasicDataContainers/Vector2D.h"


namespace ProjectAlpha {

SDL_Surface* GetSurface(std::string fileName);

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

Rect GetBindingBox(std::string fileName, Rect src);

}

