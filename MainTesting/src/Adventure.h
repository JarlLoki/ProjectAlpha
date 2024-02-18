#pragma once
#include "ProjectAlpha.h"


namespace Adventure {
enum Animations {
	idle
};

namespace States {
enum {
	idle,
	run,
	jump,
	falling,
	attack

};
}

void InitAnimations(ProjectAlpha::AnimatorComponent& animator) {
	ProjectAlpha::AnimationProperties props;
	props.SpriteSheet = "assets/images/adventurer_sprite_sheet_v1.1.png";
	props.FrameWidth = 32;
	props.FrameHeight = 32;
	props.SheetCol = 0;

	//Idle
	props.NumOfFrames = 13;
	props.SheetRow = 0;
	props.AnimationID = Animations::idle;
	props.FrameDelay = 150;

	animator.Animations[Animations::idle] = { props };

}

class Idle : public ProjectAlpha::State {
	void OnStart() override {
		m_entity.Get<Components::Animator>().Start(Animations::idle, true);
	}
	void OnUpdate() override {
		//is on ground?
		if (false) {
			m_stateMachine->SetState(States::falling);
		}
		//If a or d is pressed
		if (false) {
			m_stateMachine->SetState(States::run);
		}
		//if space pressed
		if (false) {
			m_stateMachine->SetState(States::jump);
		}
		//if attack pressed
		if (false) {
			m_stateMachine->SetState(States::attack);
		}
	}
};

void Create(ProjectAlpha::Entity e) {
	auto& transform = e.Add<Components::Transform>();
	auto& sprite = e.Add<ProjectAlpha::SpriteComponent>();
	auto& anim = e.Add<ProjectAlpha::AnimatorComponent>();

	transform.Position = { 100, 100 };
	//transform.Scale = 2.0f;

	InitAnimations(anim);
	anim.Start(Animations::idle, true);
}

}