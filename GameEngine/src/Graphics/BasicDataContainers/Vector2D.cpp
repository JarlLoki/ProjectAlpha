#include "Vector2D.h"

#include <cmath>
#include "Point.h"

namespace ProjectAlpha {

void Vector2D::SetState(float nX, float nY) {
	x = nX;
	y = nY;
}

Point Vector2D::ToPoint() {
	return Point(static_cast<int>(x), static_cast<int>(y));
}


void Vector2D::Normalize() {
	float mag = Magnitude();
	if (mag > 0) {
		this->x /= mag;
		this->y /= mag;
	}
}

float Vector2D::Magnitude() {
	float result = std::sqrt((x * x) + (y * y));
	return result;
}

//OPERATOR =
void Vector2D::operator=(const float val) {
	x = val;
	y = val;
}
// OPERATOR +
Vector2D Vector2D::operator+(const Vector2D& vector2) {
	Vector2D result(this->x + vector2.x, this->y + vector2.y);
	return result;
}
Vector2D Vector2D::operator+(const float rval) {
	Vector2D result(this->x + rval, this->y + rval);
	return result;
}

// OPREATOR -
Vector2D Vector2D::operator-(const Vector2D& vector2) {
	Vector2D result(this->x - vector2.x, this->y - vector2.y);
	return result;
}
Vector2D Vector2D::operator-(const float rval) {
	Vector2D result(this->x - rval, this->y - rval);
	return result;
}

//OPERATOR *
Vector2D Vector2D::operator*(const Vector2D& vector2) {
	Vector2D result(this->x * vector2.x, this->y * vector2.y);
	return result;
}
Vector2D Vector2D::operator*(const float rval) {
	Vector2D result(this->x * rval, this->y * rval);
	return result;
}

//OPERATOR /
Vector2D Vector2D::operator/(const Vector2D& vector2) {
	Vector2D result(this->x / vector2.x, this->y / vector2.y);
	return result;
}
Vector2D Vector2D::operator/(const float rval) {
	Vector2D result(this->x / rval, this->y / rval);
	return result;
}

//OPERATOR +=
Vector2D& Vector2D::operator+=(const Vector2D& vector2) {
	this->x += vector2.x;
	this->y += vector2.y;
	return *this;
}
Vector2D& Vector2D::operator+=(const float rval) {
	this->x += rval;
	this->y += rval;
	return *this;
}

//OPERATOR -=
Vector2D& Vector2D::operator-=(const Vector2D& vector2) {
	this->x -= vector2.x;
	this->y -= vector2.y;
	return *this;
}
Vector2D& Vector2D::operator-=(const float rval) {
	this->x -= rval;
	this->y -= rval;
	return *this;
}


//OPREATOR *=
Vector2D& Vector2D::operator*=(const Vector2D& vector2) {
	this->x *= vector2.x;
	this->y *= vector2.y;
	return *this;
}
Vector2D& Vector2D::operator*=(const float rval) {
	this->x *= rval;
	this->y *= rval;
	return *this;
}

//OPERATOR /=
Vector2D& Vector2D::operator/=(const Vector2D& vector2) {
	this->x /= vector2.x;
	this->y /= vector2.y;
	return *this;
}
Vector2D& Vector2D::operator/=(const float rval) {
	this->x /= rval;
	this->y /= rval;
	return *this;
}


//OPERATOR <
bool Vector2D::operator< (const Vector2D& vector2) {
	if (this->y < vector2.y) {
		return true;
	} else if (this->y == vector2.y) {
		if (this->x < vector2.x)
			return true;
		else
			return false;
	} else
		return false;
}

//OPERATOR >
bool Vector2D::operator> (const Vector2D& vector2) {
	if (this->y > vector2.y) {
		return true;
	} else if (this->y == vector2.y) {
		if (this->x > vector2.x)
			return true;
		else
			return false;
	} else
		return false;
}

//OPERATOR ==
bool Vector2D::operator== (const Vector2D& vector2) {
	if (this->x == vector2.x && this->y == vector2.y)
		return true;
	else
		return false;
}

bool Vector2D::operator== (int val) {
	if (this->x == val && this->y == val)
		return true;
	else
		return false;
}

//OPERATOR !=
bool Vector2D::operator!= (const Vector2D& vector2) {
	if (this->x != vector2.x || this->y != vector2.y)
		return true;
	else
		return false;
}
bool Vector2D::operator!= (int val) {
	if (this->x != val || this->y != val)
		return true;
	else
		return false;
}


}//End NameSpace