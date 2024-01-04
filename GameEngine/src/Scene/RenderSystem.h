#pragma once
#include "System.h"
#include "../Graphics/Renderer.h"
#include "Components.h"

namespace ProjectAlpha {

struct RenderSystem : public System {

	void OnRender(Renderer& renderer) override {
		
		//m_scene->GetEntities();

		//Find Camera Component
		//*
		auto cameraView = m_scene->GetEntities().view<CameraComponent, TransformComponent>();
		for (auto camera : cameraView) {

			auto view = m_scene->GetEntities().view<TransformComponent, SquareComponent>();
			for (auto entity : view) {
				auto& transform = view.get<TransformComponent>(entity);
				auto& square = view.get<SquareComponent>(entity);

				Rect rect{ static_cast<int>(transform.Position.x),
						   static_cast<int>(transform.Position.y),
						   static_cast<int>(square.width * transform.Scale),
						   static_cast<int>(square.height * transform.Scale) };

				//apply view scaler
				rect.x -= cameraView.get<TransformComponent>(camera).Position.x;
				rect.y -= cameraView.get<TransformComponent>(camera).Position.y;

				float scale = cameraView.get<CameraComponent>(camera).ZoomScale;
				renderer.DrawRect(rect, square.color, true, scale);
			}
		}

		//*/
	}
};

}//END namespace ProjectAlpha

