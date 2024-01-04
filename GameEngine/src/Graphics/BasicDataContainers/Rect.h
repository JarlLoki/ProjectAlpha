#pragma once


namespace ProjectAlpha {

struct Rect {
	int x;
	int y;
	int w;
	int h;

	Rect(int nX = 0, int nY = 0, int nW = 0, int nH = 0);

	//SDL_Rect ToSDL_Rect() const;

	void operator*=(const float& rv_float);
	void operator=(const int& rv_int);
};

inline bool operator==(const Rect& lv, const int& rv_int);

inline Rect operator*(const Rect& lv, const float& rv_float);


}