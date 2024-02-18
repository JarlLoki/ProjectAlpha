#pragma once
#include "ECS/System.h"

namespace ProjectAlpha {

struct MovementSystem : public System {
	void OnUpdate() override {
		auto view = m_scene->GetRegistry().view<TransformComponent, 
                                    			PhysicsComponent>(entt::exclude<ParentComponent>);

		for (auto entity : view){
			auto& transform = view.get<TransformComponent>(entity);
			auto& physics = view.get<PhysicsComponent>(entity);

			physics.Direction.Normalize();
			Vector2D velocity = physics.Direction * physics.Speed;

			if (physics.IsMovable) {
				transform.Position += velocity;
			}

		}
	}
};

}//END namespace ProjectAlpha 