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
		//can't sort this?
		auto entities = m_scene->GetEntitiesWith<SpriteComponent, 
			TransformComponent>();

		/*
		* using a group instead which I was able to sort
		*/
		auto group = m_scene->GetRegistry().group<SpriteComponent>(entt::get<TransformComponent>);
		//Sort algo:
		group.sort([group](const entt::entity a, const entt::entity b) {
			auto e1Transform = group.get<TransformComponent>(a);
			const auto& e1sprite = group.get<SpriteComponent>(a);

			auto e2Transform = group.get<TransformComponent>(b);
			const auto& e2sprite = group.get<SpriteComponent>(b);

			/*TODO: Add sorting by position!*/

			//Only checking for layer right now:
			//If in a lower layer then draw first:
			return e1sprite.DrawLayer < e2sprite.DrawLayer;
			});

		/*
		*Was able to just swamp the view for the group and all the existing
		*code worked!
		*/
		for (auto entityID : group) {

			Entity entity = { entityID, m_scene };

			//This might not be optimizied: ???
			//auto transform = entity.Get<TransformComponent>();
			//auto& sprite = entity.Get<SpriteComponent>();

			//I think this is more optimizied:
			auto transform = entities.get<TransformComponent>(entityID);
			const auto& sprite = entities.get<SpriteComponent>(entityID);

			if (entity.Has<ParentComponent>()) {
				Entity parent = entity.Get<ParentComponent>().Parent;
				transform.Position += parent.Get<TransformComponent>().Position;
			}

			m_game->GetRenderer().DrawSprite(sprite, transform, viewScalar, zoomScale);			

		}
	}

	//Render Hitboxes:	
	//////////////////
	if (m_game->GetRenderer().DrawHitBoxes()) {
		auto entities = m_scene->GetEntitiesWith<TransformComponent, ColliderComponent>();
		for (auto entityID : entities) {
			auto transform = entities.get<TransformComponent>(entityID);
			const auto& collider = entities.get<ColliderComponent>(entityID);

			//Get the collider rect;
			Rect rect = collider.rect;

			//add entities tranform position to the rect:
			rect.x += (int)transform.Position.x;
			rect.y += (int)transform.Position.y;

			//If it has a parent then add its parent position as well:
			Entity entity = { entityID, m_scene };
			if (entity.Has<ParentComponent>()) {
				auto parent = entity.Get<ParentComponent>().Parent;
				auto parentPos = parent.Get<TransformComponent>().Position;
				rect.x += (int)parentPos.x;
				rect.y += (int)parentPos.y;
			}
			m_game->GetRenderer().DrawRect(rect, { 255,0,0,0 }, false, 1);
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
	//m_game->GetRenderer().DrawBufferToWindow();

}











}//END namespace ProjectAlpha

