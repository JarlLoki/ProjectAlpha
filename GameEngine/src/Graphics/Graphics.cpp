
#include "Game.h"
#include "Graphics.h"

namespace ProjectAlpha {
Size GetDesktopDisplayResolution() {
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	return Size(dm.w, dm.h);
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
Rect GetBindingBox(std::string fileName) {
	SDL_Surface* surface = Game::ImageAssets.GetImage(fileName).Data;
	return GetBindingBox(surface);
}

Rect GetBindingBox(std::string fileName, Rect src) {
	//SDL_Surface* surface = GetSurface(fileName);
	SDL_Surface* surface = Game::ImageAssets.GetImage(fileName).Data;
	return GetBindingBox(surface, src);
}
////////////////////


}//END namespace ProjectAlpha
      
