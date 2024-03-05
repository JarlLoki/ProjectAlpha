#pragma once
#include "../src/Game.h"
#include "../src/Graphics/Graphics.h"
#include "../src/Graphics/Sprite.h"
//#include "../src/Graphics/Animation.h"

#include "../src/Input/Keyboard.h"

#include "../src/ECS/Entity.h"
#include "../src/ECS/Scene.h"
#include "../src/ECS/System.h"
#include "../src/ECS/Components/Components.h"
#include "../src/ECS/Components/ScriptComponent.h"
#include "../src/ECS/Components/AnimatorComponent.h"
#include "../src/ECS/Components/StateMachineComponent.h"

namespace PA = ProjectAlpha;

namespace Components {
	using Tag = ProjectAlpha::TagComponent;
	using Transform = ProjectAlpha::TransformComponent;
	using Physics = ProjectAlpha::PhysicsComponent;
	using Collider = ProjectAlpha::ColliderComponent;
	using Camera = ProjectAlpha::CameraComponent;
	using Text = ProjectAlpha::TextComponent;	
	using Sprite = ProjectAlpha::SpriteComponent;
	using Animator = ProjectAlpha::AnimatorComponent;
	using StateMachine = ProjectAlpha::StateMachineComponent;
	using Script = ProjectAlpha::ScriptComponent;
	using Parent = ProjectAlpha::ParentComponent;
	using Children = ProjectAlpha::ChildrenComponent;
	
}
