#pragma once
#include "../src/Game.h"
#include "../src/ECS/Scene.h"
#include "../src/ECS/Components/Components.h"
#include "../src/ECS/Components/ScriptComponent.h"
#include "../src/Graphics/BasicDataContainers/Rect.h"

namespace Components {
	using Tag = ProjectAlpha::TagComponent;
	using Transform = ProjectAlpha::TransformComponent;
	using Physics = ProjectAlpha::PhysicsComponent;
	using Camera = ProjectAlpha::CameraComponent;
	using Text = ProjectAlpha::TextComponent;
	
}
