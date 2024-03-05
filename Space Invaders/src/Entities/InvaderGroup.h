#pragma once
#include "ProjectAlpha.h"

#include "Invader.h"

namespace Entities::InvaderGroup {


struct Props {
	int Collums = 1;
	int Rows = 1;
};
namespace Scripts {
struct Logic : public ProjectAlpha::Script {
	void OnInit() override {
		m_startingInvaders = m_entity.Get<Components::Children>().Children.size();
	}
	void OnUpdate() override {
		//Adjust the speed of moving the group determined by how many
		//invaders are left
		int currNum = m_entity.Get<Components::Children>().Children.size();
		int numKilled = m_startingInvaders - currNum;
		float speed = 0;
		if (currNum > (m_startingInvaders / 2))
			speed = numKilled * 0.045f;
		if (currNum <= (m_startingInvaders / 2))
			speed = numKilled * 0.06;
		if (currNum < 6)
			speed = numKilled * 0.08;
		if (currNum == 1)
			speed = 9;
		if (currNum == 0)
			m_entity.Get<Components::Physics>().Direction = 0;
		m_entity.Get<Components::Physics>().Speed = speed + 1;
		//m_timeDelay = 1100 - (int)((speed * 100));


		//Find the bindingbox around existing Invaders in the grid:
		PA::Size screenSize = m_game->GetRenderer().GetLogicalRenderSize();
		ProjectAlpha::Rect bindingbox = { screenSize.w,
										  screenSize.h,
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
		bindingbox.w -= bindingbox.x;
		bindingbox.h -= bindingbox.y;
		m_entity.Get<Components::Collider>().rect = bindingbox;

		bindingbox.x += m_entity.Get<Components::Transform>().Position.x;
		bindingbox.y += m_entity.Get<Components::Transform>().Position.y;

		//Update collider - for debugging


		//Keep the group from going past the viewport and
		//If the group has reached the end of the screen then
		//lower the group by one row
		int viewportW = m_game->GetRenderer().GetLogicalRenderSize().w;

		if (bindingbox.x + bindingbox.w >= viewportW) {
			m_entity.Get<Components::Physics>().Direction.x = -1.0f;
			m_entity.Get<Components::Transform>().Position.y += height;
		} else if (bindingbox.x <= 0) {
			m_entity.Get<Components::Physics>().Direction.x = 1.0f;
			m_entity.Get<Components::Transform>().Position.y += height;
		}
		
	}
	int m_startingInvaders = 0;
};
}//END namespace Scripts

ProjectAlpha::Entity Create(ProjectAlpha::Scene* scene, Props props) {
	auto invaderGroup = scene->CreateEntity("InvaderGroup");
	invaderGroup.Add<Components::Transform>(0, 0);
	
	auto& collider = invaderGroup.Add<Components::Collider>();
	collider.Tag = "InvaderGroup";
	collider.IsSold = false;

	auto& physics = invaderGroup.Add<Components::Physics>();
	physics.Direction.x = 1.0f;
	physics.Speed = 0.5;

	auto& children = invaderGroup.Add<Components::Children>();
	//Create Invaders:
	int w = 32;
	int h = 32;
	for (int r = 0; r < props.Rows; r++) {
		for (int c = 0; c < props.Collums; c++) {
			auto invader = Entities::Invader::Create(scene);
			invader.Get<Components::Transform>().Position = { c * w, r * h };
			invader.Get<Components::Parent>().Parent = invaderGroup;
			children.Children.push_back(invader);
		}
	}

	auto& scripts = invaderGroup.Add<Components::Script>(invaderGroup);
	scripts.Add<Scripts::Logic>();

	return invaderGroup;
}

}//END namespace InvaderGroup