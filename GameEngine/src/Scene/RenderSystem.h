#pragma once
#include "System.h"
#include "../Graphics/Renderer.h"
#include "Components.h"

namespace ProjectAlpha {

struct RenderSystem : public System {
	void OnRender(Renderer& renderer) override;
};

void RenderSystem::OnRender(Renderer& renderer) {

	//m_scene->GetEntities();

	//Find Camera Component
	//*
	auto cameraView = m_scene->GetRegistry().view<CameraComponent,
		TransformComponent>();

	auto camera = cameraView.front();

	//Get view scaler (replace this with a view matrix?)
	const float zoomScale = cameraView.get<CameraComponent>(camera).ZoomScale;
	const Vector2D viewPort = { renderer.GetViewPortWidth(),
							  renderer.GetViewPortHeight() };

	//Vector2D cameraSize = viewPort - (viewPort * (zoomScale - 1));
	//Vector2D cameraSize = viewPort * (viewPort / (viewPort * zoomScale));
	Vector2D cameraSize = viewPort / zoomScale;

	Vector2D cameraPos = cameraView.get<TransformComponent>(camera).Position;
	Vector2D cameraOffset = cameraView.get<CameraComponent>(camera).offSet;
	Vector2D viewScalar = cameraPos - (cameraSize / 2) + cameraOffset;


	{
		auto view = m_scene->GetRegistry().view<TransformComponent,
			SquareComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& square = view.get<SquareComponent>(entity);

			
			Rect rect{ static_cast<int>(transform.Position.x - viewScalar.x),
					   static_cast<int>(transform.Position.y - viewScalar.y),
					   static_cast<int>(square.width * transform.Scale),
					   static_cast<int>(square.height * transform.Scale) };

			renderer.DrawRect(rect, square.color, true, zoomScale);
		}
	}
	{
		auto group = m_scene->GetRegistry().group<TransformComponent,
			TextComponent>();
		for (auto entity : group) {
			auto& transform = group.get<TransformComponent>(entity);
			auto& cText = group.get<TextComponent>(entity);

			//Create a Text
			Text uText = { cText.FontName, cText.FontSize,
						   cText.Text, cText.Color };

			//If Text isnt rendered yet, or Text =/= Rendered Text
			if (cText.RenderedText == nullptr || *cText.RenderedText != uText) {
				//Render Text
				cText.RenderedText = renderer.RenderText(uText);
			}
			//Draw Rendered Text
			if (cText.RenderedText) {

				Vector2D position{ transform.Position.x + cText.Position.x,
							   transform.Position.y + cText.Position.y };	

				renderer.DrawTexture(cText.RenderedText->GetTexture(), 
							         position - viewScalar, zoomScale);
			}
			//Text couldnt be rendered, unable to draw
			else {
				PA_LOG_ERROR("Unable to render text.");
			}

		}

	}
}












}//END namespace ProjectAlpha

