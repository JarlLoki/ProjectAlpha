#pragma once
#include "ProjectAlpha.h"

#include "Invader.h"

namespace Entities::InvaderGroup {

class Logic : public ProjectAlpha::Script {
	void OnUpdate() override {
		
	}
};

struct Props {
	int Collums = 1;
	int Rows = 1;
};

class Logic : public ProjectAlpha::Script {
	void OnUpdate() override {

		//Adjust the speed of moving the group determined by how many
		//invaders are left


		//Find the bindingbox around existing Invaders in the grid:
		ProjectAlpha::Rect bindingbox = { m_game->GetWindow().GetWidth(),
										  m_game->GetWindow().GetHeight(),
										  0, 0 };
		int width = 0;
		int height = 0;
		for (auto child : m_entity.Get<Components::Children>().Children) {
			auto& transform = child.Get<Components::Transform>();
			width = child.Get<Components::Sprite>().Sprite.SrcRect.w;
			height = child.Get<Components::Sprite>().Sprite.SrcRect.h;
			bindingbox.x = std::min(bindingbox.x, (int)transform.Position.x);
			bindingbox.y = std::min(bindingbox.y, (int)transform.Position.y);
			bindingbox.w = std::max(bindingbox.w, (int)transform.Position.x + width);
			bindingbox.h = std::max(bindingbox.h, (int)transform.Position.y + height);
		}
		bindingbox.x = m_entity.Get<Components::Transform>().Position.x;
		bindingbox.y = m_entity.Get<Components::Transform>().Position.y;

		//Keep the group from going past the viewport and
		//If the group has reached the end of the screen then
		//lower the group by one row
		int viewportW = m_game->GetRenderer().GetViewPortWidth();
		int viewpportH = m_game->GetRenderer().GetViewPortHeight();

		if (bindingbox.x + bindingbox.w >= viewportW) {
			m_entity.Get<Components::Physics>().Direction = -1.0f;
			m_entity.Get<Components::Transform>().Position.y += height;
		} else if (bindingbox.x <= 0) {
			m_entity.Get<Components::Physics>().Direction = 1.0f;
			m_entity.Get<Components::Transform>().Position.y += height;
		}


		

	}
};

ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene, Props props) {
	auto invaderGroup = scene->CreateEntity("InvaderGroup");
	int w = 32;
	int h = 32;

	for (int r = 0; r < props.Rows; r++) {
		for (int c = 0; c < props.Collums; c++) {
			auto invader = Entities::SpaceInvader::Create(scene);
			invader.Get<Components::Transform>().Position = { c * w, r * h };
			invader.Get<Components::Parent>().Parent = invaderGroup;
		}
	}
	

	return invaderGroup;
}

}//END namespace InvaderGroup