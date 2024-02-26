#pragma once
#include "Game.h"
#include "ECS/System.h"
#include "ECS/Components/Components.h"
#include "Graphics/Renderer.h"


namespace ProjectAlpha {

struct RenderSystem : public System {
	//void OnRender(Renderer& renderer) override;
	void OnUpdate() override;
};

void RenderSystem::OnUpdate() {
	m_game->GetRenderer().ResetDrawBuffer();
	
	//Find Camera:
	//////////////////
	auto cameras = m_scene->GetEntitiesWith<CameraComponent, 
		TransformComponent>();

	//For now just find the first camera
	Entity camera;
	if (cameras.size_hint() > 0)
		camera = { cameras.front(), m_scene };
	else
		camera = {};

	const float zoomScale = camera.Get<CameraComponent>().ZoomScale;
	const Vector2D viewPort = { m_game->GetWindow().GetWidth(),
								m_game->GetWindow().GetHeight() };

	Vector2D cameraSize = viewPort / zoomScale;

	Vector2D cameraPos = camera.Get<TransformComponent>().Position;
	Vector2D cameraOffset = camera.Get<CameraComponent>().offSet;

	Vector2D viewScalar;
	if (camera.Get<CameraComponent>().Center)
		viewScalar = cameraPos - (cameraSize / 2) + cameraOffset;
	else
		viewScalar = cameraPos + cameraOffset;

	//Render Sprites:
	//////////////////
	{
		auto entities = m_scene->GetEntitiesWith<SpriteComponent, 
			TransformComponent>();
		for (auto entityID : entities) {

			Entity entity = { entityID, m_scene };

			//This might not be optimizied: ???
			//auto transform = entity.Get<TransformComponent>();
			//auto& sprite = entity.Get<SpriteComponent>();

			//I think this is more optimizied:
			auto transform = entities.get<TransformComponent>(entityID);
			auto& sprite = entities.get<SpriteComponent>(entityID);

			if (entity.Has<ParentComponent>()) {
				Entity parent = entity.Get<ParentComponent>().Parent;
				transform.Position += parent.Get<TransformComponent>().Position;
			}

			m_game->GetRenderer().DrawSprite(sprite, transform, viewScalar, zoomScale);			

		}
	}


	//Render Primitives:	
	//////////////////
	{
		auto entities = m_scene->GetEntitiesWith<TransformComponent, 
			SquareComponent>();

		for (auto id : entities) {
			Entity entity = m_scene->GetEntity(id);
			auto& transform = entity.Get<TransformComponent>();
			auto& square = entity.Get<SquareComponent>();

			Vector2D parentPos = 0;
			if (entity.Has<ParentComponent>()) {
				Entity parent = entity.Get<ParentComponent>().Parent;
				parentPos = parent.Get<TransformComponent>().Position;
			}

			Rect rect{ static_cast<int>(transform.Position.x + parentPos.x) - (int)viewScalar.x,
					   static_cast<int>(transform.Position.y + parentPos.y) - (int)viewScalar.y,
					   static_cast<int>(square.width * transform.Scale),
					   static_cast<int>(square.height * transform.Scale) };

			m_game->GetRenderer().DrawRect(rect, square.color, true, zoomScale);
		}
	}
	
	//Render Text
	//////////////////
	{
		auto group = m_scene->GetRegistry().group<TransformComponent,
			TextComponent>();

		auto group2 = m_scene->GetEntitiesWith<TransformComponent, TextComponent>();
		for (auto entityID : group) {
			Entity entity = { entityID, m_scene };
			auto& transform = entity.Get<TransformComponent>();
			auto& cText = entity.Get<TextComponent>();
			 


			//Create a Text
			Text uText = { cText.FontName, cText.FontSize,
						   cText.Text, cText.Color };

			//If Text isnt rendered yet, or Text =/= Rendered Text
			if (cText.RenderedText == nullptr || *cText.RenderedText != uText) {
				//Render Text
				cText.RenderedText = m_game->GetRenderer().RenderText(uText);
			}
			//Draw Rendered Text
			if (cText.RenderedText) {


				Vector2D position{ transform.Position.x + cText.Position.x,
							   transform.Position.y + cText.Position.y };

				//Add Parents position
				if (entity.Has<ParentComponent>()) {
					Entity parent = entity.Get<ParentComponent>().Parent;
					auto& parentTransform = parent.Get<TransformComponent>();
					position += parentTransform.Position;
				}

				position.x = static_cast<float>((int)position.x - (int)viewScalar.x);
				position.y = static_cast<float>((int)position.y - (int)viewScalar.y);

				m_game->GetRenderer().DrawTexture(cText.RenderedText->GetTexture(),
					position, zoomScale);
			}
			//Text couldnt be rendered, unable to draw
			else {
				PA_LOG_ERROR("Unable to render text.");
			}

		}

	}
	m_game->GetRenderer().DrawBufferToWindow();

}











}//END namespace ProjectAlpha

