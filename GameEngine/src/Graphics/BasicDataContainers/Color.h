#pragma once
#include <stdint.h>

namespace ProjectAlpha {

//COLOR
// Black = 0,0,0 White = 255,255,255
//R = red 0-255
//G = green 0-255
//B = blue 0-255
//A = Alpha 0-255 (255 is opique)
struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Color(uint8_t nR = 0, uint8_t nG = 0, uint8_t nB = 0, uint8_t nA = 0) :
		r(nR), g(nG), b(nB), a(nA) {
	}


	Color(int nR, int nG, int nB, int nA) {
		r = static_cast<uint8_t>(nR);
		g = static_cast<uint8_t>(nG);
		b = static_cast<uint8_t>(nB);
		a = static_cast<uint8_t>(nA);
	}

	Color(int nR, int nG, int nB) {
		r = static_cast<uint8_t>(nR);
		g = static_cast<uint8_t>(nG);
		b = static_cast<uint8_t>(nB);
		a = static_cast<uint8_t>(0);
	}
};

inline bool operator == (const Color& lvalue, const Color& rvalue) {
	if (lvalue.r == rvalue.r &&
		lvalue.b == rvalue.b &&
		lvalue.g == rvalue.g &&
		lvalue.a == rvalue.a) {
		return true;
	}
	return false;
}

}//End Namespace