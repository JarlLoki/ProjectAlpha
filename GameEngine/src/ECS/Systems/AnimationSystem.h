#pragma once
#include "ECS/System.h"
#include "ECS/Scene.h"

#include "ECS/Components/Components.h"
#include "ECS/Components/AnimatorComponent.h"

namespace ProjectAlpha {

struct AnimationSystem : public System {
	void OnUpdate() override;
};

void AnimationSystem::OnUpdate() {
	auto view = m_scene->GetRegistry().view<AnimatorComponent,
		SpriteComponent>();

	for (auto entity : view) {
		//Setup Variables
		///////////////////
		
		//Animator 
		auto& animator = view.get<AnimatorComponent>(entity);
	
		auto& frames = animator.Animations[animator.m_animID].Frames;

		auto pause = animator.m_pause;
		auto loop = animator.m_loop;

		auto& frameTimeDelta = animator.m_frameTimeDelta;
		auto& frameTimeStart = animator.m_frameTimeStart;
		auto frameDelay = animator.Animations[animator.m_animID].FrameDelay;

		auto& frameIndex = animator.m_frameIndex;
		auto numOfFrames = animator.Animations[animator.m_animID].Frames.size();

		//Set Reference to sprite in the Sprite Component
		auto& sprite = view.get<SpriteComponent>(entity).Sprite;

		//Update Animator 
		///////////////////
		if (!pause) {
			//Get Time Delta
			frameTimeDelta = SDL_GetTicks() - frameTimeStart;

			//Increment Frame Index
			//If frame delay time has been reached:
			if (frameTimeDelta >= frameDelay) {
				//Increment Frame
				frameIndex++;

				//If FrameIndex has gone past the number of Frames:
				if (frameIndex >= numOfFrames) {
					//If loop is true then set index to 0 and reset FrameTime
					if (loop) {
						frameIndex = 0;
						frameTimeStart = SDL_GetTicks();
						//Update Sprite
						sprite = frames[frameIndex];
					}
					//If loop isnt true then just keep it on the last frame
					//Dont reset FrameStart time
					//No Need to update sprite because it would be the same
					else {
						frameIndex = numOfFrames - 1;
					}
				}
				//hasnt gone past number of frames then reset framestart
				//and update the sprite
				else {
					frameTimeStart = SDL_GetTicks();
					//Update Sprite
					sprite = frames[frameIndex];
				}
			}
		}
	}
}

}//END namespace ProjectAlpha