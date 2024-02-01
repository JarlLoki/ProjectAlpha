#pragma once
#include <stdint.h>
#include <unordered_map>

#include "SDL.h"
#include "Graphics/Animation.h"

namespace ProjectAlpha {

struct AnimationSystem;

struct AnimatorComponent {
	std::unordered_map<AnimationID, Animation> Animations;

	void Start(AnimationID id, bool loop) {
		m_animID = id;
		m_frameIndex = 0;
		m_loop = loop;
		m_frameTimeStart = SDL_GetTicks();
	}

	bool End() {
		if (m_frameIndex >= Animations[m_animID].Frames.size() - 1 &&
			m_frameTimeDelta >= Animations[m_animID].FrameDelay) {
			return true;
		} else
			return false;
	}

	void Pause() { m_pause = true; }
	void Resume() { m_pause = false; }

	AnimationID GetAnimationID() { return Animations[m_animID].ID; }
	int GetFrameIndex() { return m_frameIndex; }

private:
	AnimationID m_animID;
	bool m_loop;
	bool m_pause;
	int m_frameIndex;
	uint32_t m_frameTimeStart;
	uint32_t m_frameTimeDelta;
	
	friend AnimationSystem;
};

} //END namespace ProjectAlpha