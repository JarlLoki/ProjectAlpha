#pragma once
#include <stdint.h>
#include <vector>

#include "Graphics/Graphics.h"
#include "Graphics/Sprite.h"

namespace ProjectAlpha {

using AnimationID = uint16_t;

struct AnimationProperties {
	unsigned int AnimationID = 0;
	std::string SpriteSheet = "";
	int NumOfFrames = 0;
	int FrameWidth = 0;
	int FrameHeight = 0;
	int SheetRow = 0;
	int SheetCol = 0;
	int FrameDelay = 0;
};

inline std::vector<Sprite> CreateFrames(std::string fileName,
	int frameW, int frameH,
	int numFrames,
	int frameRow, int frameCol) {
	std::vector<Sprite> frames;
	for (int i = 0; i < numFrames; i++) {
		Rect src = { frameW * (i + frameCol), frameH * frameRow, frameW, frameH };

		Sprite sprite;
		sprite.SpriteSheet = fileName;
		sprite.SrcRect = src;
		sprite.BindingBox = GetBindingBox(fileName, src);
	}
	return frames;
}

inline std::vector<Sprite> CreateFrames(AnimationProperties props) {
	std::vector<Sprite> frames;
	for (int i = 0; i < props.NumOfFrames; i++) {
		Rect src = { props.FrameWidth * (i + props.SheetCol),
					 props.FrameHeight * props.SheetRow,
					 props.FrameWidth,
					 props.FrameHeight };

		Sprite sprite;
		sprite.SpriteSheet = props.SpriteSheet;
		sprite.SrcRect = src;
		sprite.BindingBox = GetBindingBox(props.SpriteSheet, src);

		frames.push_back(sprite);
	}
	return frames;
}

struct Animation {
	Animation() = default;
	Animation(AnimationID id, std::vector<Sprite> frames, uint32_t delay) : 
		ID(id), Frames(frames), FrameDelay(delay) { }

	Animation(AnimationProperties props) {
		ID = props.AnimationID;
		FrameDelay = props.FrameDelay;
		Frames = CreateFrames(props);
	}

	AnimationID ID = 0;
	std::vector<Sprite> Frames;
	uint32_t FrameDelay = 0;
};

} //END namespace ProjectAlpha


/*






*/