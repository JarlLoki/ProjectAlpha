#include "Defender.h"

ProjectAlpha::Entity Entities::Defender::Create(ProjectAlpha::Scene* scene) {
	auto defender = scene->CreateEntity("Defender");
	defender.Add<Components::Transform>(0, 0);
	defender.Add<Components::Physics>();
	defender.Add<Components::Collider>();

	defender.Add<Components::StateMachine>();

	defender.Add<Components::Sprite>();
	defender.Add<Components::Animator>();

	defender.Add<Components::Script>();

	return defender;
}
