#pragma once


namespace ProjectAlpha {
struct Size;
struct Point;

struct Rect {
	int x;
	int y;
	int w;
	int h;

	Rect(int nX = 0, int nY = 0, int nW = 0, int nH = 0);
	Rect(Point point, Size size);

	//SDL_Rect ToSDL_Rect() const;

	void operator+=(const Point& rv_point);
	void operator*=(const float& rv_float);
	void operator=(const int& rv_int);
};

bool operator==(const Rect& lv, const int& rv_int);
bool operator==(const Rect& lv, const Rect& rv);

inline Rect operator+(const Point& lv, const Size& rv);
inline Rect operator*(const Rect& lv, const float& rv_float);


}