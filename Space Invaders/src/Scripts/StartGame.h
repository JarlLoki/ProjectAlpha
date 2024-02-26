#pragma once
#include "ProjectAlpha.h"
#include "SpaceInvaders.h"

namespace Scripts {
class StartGame : public ProjectAlpha::Script {
	void OnInit() {
		SpaceInvaders* spaceinvader = static_cast<SpaceInvaders*>(m_game);

		spaceinvader->Lives = 3;
		spaceinvader->Level = 0;
		spaceinvader->Score = 0;
	}
};

}