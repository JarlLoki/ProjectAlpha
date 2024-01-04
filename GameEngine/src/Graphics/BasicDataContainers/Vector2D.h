#pragma once

namespace ProjectAlpha {

struct Point;
struct Vector2D {

	float x;
	float y;

	//Vector2D(float nX = 0.0f, float nY = 0.0f) : x(nX), y(nY) {}
	Vector2D() {
		x = 0.0f;
		y = 0.0f;
	}
	Vector2D(auto p) : x(static_cast<float>(p)), y(static_cast<float>(p)) {}
	Vector2D(auto pX, auto pY) : x(static_cast<float>(pX)),
		y(static_cast<float>(pY)) {
	}

	void SetState(float nX, float nY);
	Point ToPoint();
	float Magnitude();
	void Normalize();

	void operator=(const float val);
	Vector2D operator+(const Vector2D& vector2);
	Vector2D operator+(const float rval);

	Vector2D operator-(const Vector2D& vector2);
	Vector2D operator-(const float rval);

	Vector2D operator*(const Vector2D& vector2);
	Vector2D operator*(const float rval);

	Vector2D operator/(const Vector2D& vector2);
	Vector2D operator/(const float rval);


	Vector2D& operator+=(const Vector2D& vector2);
	Vector2D& operator+=(const float rval);

	Vector2D& operator-=(const Vector2D& vector2);
	Vector2D& operator-=(const float rval);


	Vector2D& operator*=(const Vector2D& vector2);
	Vector2D& operator*=(const float rval);

	Vector2D& operator/=(const Vector2D& vector2);
	Vector2D& operator/=(const float rval);


	bool operator< (const Vector2D& vector2);
	bool operator> (const Vector2D& vector2);
	bool operator== (const Vector2D& vector2);
	bool operator!= (const Vector2D& vector2);

	bool operator== (int val);
	bool operator!= (int val);

};

}