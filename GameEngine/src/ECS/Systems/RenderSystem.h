#pragma once
#include "ECS/System.h"
#include "ECS/Components/Components.h"
#include "Graphics/Renderer.h"


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

	Vector2D viewScalar;
	if(cameraView.get<CameraComponent>(camera).Center)
		viewScalar = cameraPos - (cameraSize / 2) + cameraOffset;
	else
		viewScalar = cameraPos + cameraOffset;


	//Render Sprites
	////////////////////////////	
	{
		auto view = m_scene->GetRegistry().view<TransformComponent,
			SpriteComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& sprite = view.get<SpriteComponent>(entity);

			Rect dstRect{ static_cast<int>(transform.Position.x) - (int)viewScalar.x,
					   static_cast<int>(transform.Position.y) - (int)viewScalar.y,
		               static_cast<int>(sprite.Sprite.SrcRect.w * transform.Scale),
		               static_cast<int>(sprite.Sprite.SrcRect.h * transform.Scale) };

			renderer.DrawSprite(sprite.Sprite, dstRect, zoomScale);
		}
	}

	//Render Rectangles
	////////////////////////////
	{
		auto view = m_scene->GetRegistry().view<TransformComponent,
			SquareComponent>();
		for (auto entity : view) {
			auto& transform = view.get<TransformComponent>(entity);
			auto& square = view.get<SquareComponent>(entity);

			
			Rect rect{ static_cast<int>(transform.Position.x) - (int)viewScalar.x,
					   static_cast<int>(transform.Position.y) - (int)viewScalar.y,
					   static_cast<int>(square.width * transform.Scale),
					   static_cast<int>(square.height * transform.Scale) };

			renderer.DrawRect(rect, square.color, true, zoomScale);
		}
	}

	//Render Text
	////////////////////////////
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

				position.x = static_cast<float>((int)position.x - (int)viewScalar.x);
				position.y = static_cast<float>((int)position.y - (int)viewScalar.y);

				renderer.DrawTexture(cText.RenderedText->GetTexture(), 
							         position, zoomScale);
			}
			//Text couldnt be rendered, unable to draw
			else {
				PA_LOG_ERROR("Unable to render text.");
			}

		}

	}
}












}//END namespace ProjectAlpha

