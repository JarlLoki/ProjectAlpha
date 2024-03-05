#pragma once
#include "SDL.h"

namespace ProjectAlpha::Input::Keyboard {

/*IsPressed
* Takes an SDL Keycode and returns true if its pressed
*/
inline bool IsPressed(SDL_Scancode sdlScanCode) {
	auto state = SDL_GetKeyboardState(nullptr);
	if (state[sdlScanCode])
		return true;
	else
		return false;
}

}//END namespace ProjectAlpha 