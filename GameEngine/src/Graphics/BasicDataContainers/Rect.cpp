#include "Rect.h"


namespace ProjectAlpha {

 Rect::Rect(int nX, int nY, int nW, int nH) :
	x(nX), y(nY), w(nW), h(nH) {
}

//inline SDL_Rect Rect::ToSDL_Rect() const {
//	return SDL_Rect(x, y, w, h);
//}

 void Rect::operator*=(const float& rv_float) {
	x = static_cast<int>(x * rv_float);
	y = static_cast<int>(y * rv_float);
	w = static_cast<int>(w * rv_float);
	h = static_cast<int>(h * rv_float);
}

 void Rect::operator=(const int& rv_int) {
	x = rv_int;
	y = rv_int;
	w = rv_int;
	h = rv_int;
}

bool operator==(const Rect& lv, const int& rv_int) {
	if (lv.x == rv_int &&
		lv.y == rv_int &&
		lv.w == rv_int &&
		lv.h == rv_int)
		return true;
	return false;
}

Rect operator*(const Rect& lv, const float& rv_float) {
	Rect r;
	r.x = static_cast<int>(lv.x * rv_float);
	r.y = static_cast<int>(lv.y * rv_float);
	r.w = static_cast<int>(lv.w * rv_float);
	r.h = static_cast<int>(lv.h * rv_float);
	return r;
}

}
