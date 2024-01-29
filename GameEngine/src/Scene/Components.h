#pragma once

#include "../Graphics/BasicDataContainers/Vector2D.h"
#include "../Graphics//BasicDataContainers/Rect.h"
#include "../Graphics//BasicDataContainers/Color.h"

#include "../Graphics/Text.h"

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
	Vector2D Position = 0.0f;
	float Rotation = 0.0f;
	float Scale = 1.0f;

	TransformComponent() = default;
	TransformComponent(float x, float y) : Position({ x,y }) {}
	TransformComponent(const TransformComponent&) = default;
	//TransformComponent(Vector2D position = 
	//	{0.0f,0.0f}, float rotation = 0.0f, float scale = 1.0f)
	//	: Position(position), Rotation(rotation), Scale(scale) {}


};
using Transform = TransformComponent;


struct SquareComponent {
	int width;
	int height;
	Color color;

	SquareComponent() = default;
	//SquareComponent(const SquareComponent&) = default;
	SquareComponent(int w, int h, Color c) : width(w), height(h), color(c) {}

};


/*TODO: Change this to MoveComponent*/
struct PhysicsComponent {
	Vector2D Direction;
	float Speed = 1;
	bool IsMovable = true;

	PhysicsComponent() = default;
	//PhysicsComponent(const PhysicsComponent&) = default;
	
};

enum ColliderType {
	Rectangle,
	Sphere,
	Plane
};

struct ColliderBase {
	ColliderType type;
	bool IsSolid = true;
};

struct RectCollider : ColliderBase {
	RectCollider() { type = ColliderType::Rectangle; }
	Rect rect;
};

struct RigidBody {
	
};

struct ColliderComponent {
public:
	ColliderComponent() = default;
	ColliderComponent(int x, int y, int w, int h) : rect({ x,y,w,h }) {}

	std::string Tag = "";
	Rect rect = { 0,0,0,0 };
	bool IsSold = true;

	void BindOnCollision(void(*funcptr)(Entity, Entity)) {
		m_OnCollideFunction = funcptr;
	}

	void OnCollision(Entity entityA, Entity entityB) {
		if (m_OnCollideFunction) {
			m_OnCollideFunction(entityA, entityB);
		}
	}

private:
	void(*m_OnCollideFunction)(Entity, Entity) = nullptr;
	
};


struct CameraComponent {
	int ViewWidth;
	int ViewHeight;
	float ZoomScale;
	Vector2D offSet;

	CameraComponent() = default;
	//CameraComponent(const CameraComponent&) = default;
};

struct TextComponent {
	Vector2D Position = 0;
	std::string Text;
	std::string FontName;
	int FontSize;
	Color Color;

	std::unique_ptr<RenderedText> RenderedText = nullptr;

	TextComponent() = default;
	//TextComponent(const TextComponent&) = default;
};


} //END namespace ProjectAlpha