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



				//Get view scaler (replace this with a view matrix?)
				const float zoomScale = cameraView.get<CameraComponent>(camera).ZoomScale;
				const Vector2D viewPort = { renderer.GetViewPortWidth(),
				     					  renderer.GetViewPortHeight() };

				//Vector2D cameraSize = viewPort - (viewPort * (zoomScale - 1));
				Vector2D cameraSize = viewPort * (viewPort / (viewPort * zoomScale));
				Vector2D cameraPos = cameraView.get<TransformComponent>(camera).Position;
				Vector2D cameraOffset = cameraView.get<CameraComponent>(camera).offSet;
				Vector2D viewScalar = cameraPos - (cameraSize / 2) + cameraOffset;

				//apply view scaler				
				//rect.x -= static_cast<int>(viewScalar.x);
				//rect.y -= static_cast<int>(viewScalar.y);
				
				

				
				Rect rect{ static_cast<int>(transform.Position.x-viewScalar.x),
						   static_cast<int>(transform.Position.y-viewScalar.y),
		                   static_cast<int>(square.width * transform.Scale),
		                   static_cast<int>(square.height * transform.Scale) };
				
				

				
				renderer.DrawRect(rect, square.color, true, zoomScale);
			}
		}

		//*/
	}
};

}//END namespace ProjectAlpha

