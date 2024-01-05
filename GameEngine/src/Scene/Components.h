#pragma once

#include "../Graphics/BasicDataContainers/Vector2D.h"
#include "../Graphics//BasicDataContainers/Rect.h"
#include "../Graphics//BasicDataContainers/Color.h"

namespace ProjectAlpha {

struct TagComponent {
	inline std::string GetTag() const { return m_Tag; }

	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag) : m_Tag(tag) {}


	operator const std::string& () const { return m_Tag; }
private:
	std::string m_Tag;

};

struct TransformComponent {
	Vector2D Position;
	float Rotation;
	float Scale;

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(Vector2D position = 
		{0.0f,0.0f}, float rotation = 0.0f, float scale = 1.0f)
		: Position(position), Rotation(rotation), Scale(scale) {}


};



struct SquareComponent {
	int width;
	int height;
	Color color;

	SquareComponent() = default;
	SquareComponent(const SquareComponent&) = default;
	SquareComponent(int w, int h, Color c) : width(w), height(h), color(c) {}

};


struct PhysicsComponent {
	Vector2D Direction;
	float Speed = 1;
	bool IsMovable = true;

	PhysicsComponent() = default;
	
};

struct CameraComponent {
	int ViewWidth;
	int ViewHeight;
	float ZoomScale;

	Window* window;
};




} //END namespace ProjectAlpha