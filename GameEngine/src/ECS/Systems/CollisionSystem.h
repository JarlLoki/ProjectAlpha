#pragma once
#include "ECS/System.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"

#include "ECS/Components/Components.h"
#include "Graphics/BasicDataContainers/Rect.h"

namespace ProjectAlpha {

inline bool AABB(Rect hitboxA, Rect hitboxB) {

	if (hitboxA.x + hitboxA.w >= hitboxB.x &&
		hitboxB.x + hitboxB.w >= hitboxA.x &&
		hitboxA.y + hitboxA.h >= hitboxB.y &&
		hitboxB.y + hitboxB.h >= hitboxA.y) {

		return true;
	}
	return false;
}


void ResolveSolidCollision(Entity entityA,
	TransformComponent& transformA,
	Rect hitboxA,
	Entity entityB,
	TransformComponent& transformB,
	Rect hitboxB) {

	//Get EntityA current hitbox
	Rect curHitboxA = hitboxA;

	//Get EntityA previous hitbox
	//If it has a parent, adds parent position! //TODO
	Rect prevHitboxA = curHitboxA;
	if (entityA.Has<PhysicsComponent>()) {
		auto& physicsA = entityA.Get<PhysicsComponent>();
		Vector2D prevPosA;
		prevPosA = transformA.Position - (physicsA.Direction * physicsA.Speed);
		Vector2D offset = prevPosA - transformA.Position;

		prevHitboxA.x += static_cast<int>(offset.x);
		prevHitboxA.y += static_cast<int>(offset.y);

	}

	//Get EntityB current hitbox
	Rect curHitboxB = hitboxB;

	//Get EntityA previous hitbox
	//If it has a parent, adds parent position! //TODO
	Rect prevHitboxB = curHitboxB;
	if (entityB.Has<PhysicsComponent>()) {
		auto& physicsB = entityB.Get<PhysicsComponent>();
		Vector2D prevPosB;
		prevPosB = transformB.Position - (physicsB.Direction * physicsB.Speed);
		Vector2D offset = prevPosB - transformB.Position;

		prevHitboxB.x += static_cast<int>(offset.x);
		prevHitboxB.y += static_cast<int>(offset.y);

	}

	//Get if objects are movable:
	bool isAMovable;
	bool isBMovable;
	if (entityA.Has<PhysicsComponent>()) {
		isAMovable = entityA.Get<PhysicsComponent>().IsMovable;
	} else
		isAMovable = false;

	if (entityB.Has<PhysicsComponent>()) {
		isBMovable = entityB.Get<PhysicsComponent>().IsMovable;
	} else
		isBMovable = false;

	//Get the amount of overlap on the two hitboxes
	Vector2D overlap = 0;
	overlap.x = static_cast<float>(
		std::min(curHitboxA.x + curHitboxA.w, curHitboxB.x + curHitboxB.w) -
		std::max(curHitboxA.x, curHitboxB.x)
		);

	overlap.y = static_cast<float>(
		std::min(curHitboxA.y + curHitboxA.h, curHitboxB.y + curHitboxB.h ) - 
		std::max(curHitboxA.y, curHitboxB.y)
		);

	//These Vectors will be used to move the entities:
		//Add the overlap to the move vectors:
	Vector2D moveA = overlap;
	Vector2D moveB = overlap;

	if (overlap.x > overlap.y) {
		moveA.x = 0;
		moveB.x = 0;
	}
	if (overlap.y > overlap.x) {
		moveA.y = 0;
		moveB.y = 0;

	}


	//Bunch of over logic stuff that is applied to the move vectors
	//to device if A or B should be moving and by how much
	/* TODO:
	* I forgot what most of this stuff does but it works
	* kind of?
	* I feel like a lot of this can be simplified or improved.
	*/
	//If Both Moved
	if (prevHitboxA != curHitboxA && prevHitboxB != curHitboxB) {
		//If both are movable:
		if (isAMovable && isBMovable) {
			Vector2D moveAi = moveA;
			Vector2D moveBi = moveB;
			//while (moveAi > 0 && moveBi > 0) {

			//}

		} else if (isAMovable) {
			//Dont MoveB
			moveB = 0;
		} else if (isBMovable) {
			//Dont Move A
			moveA = 0;
		}
		//None are Movable
		else {
			//Dont move anything
			moveA = 0;
			moveB = 0;
		}
	}
	//If Only A moved
	//Then we dont want to move B
	else if (prevHitboxA != curHitboxA) {
		moveB = 0;

	}
	//If Only B moved
	//Then we dont want to move A
	else if (prevHitboxB != curHitboxB) {
		moveA = 0;
	}
	//NONE MOVED!
	//So we split the amount moved by both if they are movable objects:
	else {
		if (isAMovable && isBMovable) {

			moveA /= 2;
			moveB /= 2;

		} else if (isAMovable) {
			//Dont MoveB
			moveB = 0;
		} else if (isBMovable) {
			//Dont Move A
			moveA = 0;
		}
		//None are Movable
		else {
			//Dont move anything
			moveA = 0;
			moveB = 0;
		}

	}

	/*
	* Forgot what this was for:
	* I think this changes to move vector direction based on where the two
	* objects are to each other
	*/
	if (prevHitboxA.x < prevHitboxB.x) {
		moveA.x *= -1;
	} else {
		moveB.x *= -1;
	}

	if (prevHitboxA.y < prevHitboxB.y)
		moveA.y *= -1;
	else
		moveB.y *= -1;

	//Apply the move vectors to the entites:
	transformA.Position += moveA;
	transformB.Position += moveB;
}


struct CollisionSystem : public System {

	void OnUpdate() override {
		//*
		auto view = m_scene->GetRegistry().view<ColliderComponent, 
												  TransformComponent>();
		for (auto itL = view.begin(); itL != view.end(); ++itL) {
			for (auto itR = std::next(itL); itR != view.end(); ++itR) {
				//*
				//Get Entity IDs:
				auto entityidA = *itL;
				auto entityidB = *itR;

				//Get Entity from IDs:
				Entity entityA = m_scene->GetEntity(entityidA);
				Entity entityB = m_scene->GetEntity(entityidB);

				//Get the Transforms and Colliders for both Entity A and B:
				auto& transformA = view.get<TransformComponent>(entityidA);
				auto& colliderA = view.get<ColliderComponent>(entityidA);

				auto& transformB = view.get<TransformComponent>(entityidB);
				auto& colliderB = view.get<ColliderComponent>(entityidB);	
				
				bool test = false;
				if (colliderA.Tag == "Bullet" && colliderB.Tag == "Invader") {
					test = true;
				}

				//Create Entity A and B hitboxes:
				//If it has a parent, adds parent position!
				Rect hitboxA;
				Vector2D posA = transformA.Position;
				if (entityA.Has<ParentComponent>()) {
					Entity parent = entityA.Get<ParentComponent>().Parent;
					posA += parent.Get<TransformComponent>().Position;
				}
				hitboxA = colliderA.rect;
				hitboxA.x += static_cast<int>(posA.x);
				hitboxA.y += static_cast<int>(posA.y);
			

				Rect hitboxB;
				Vector2D posB = transformB.Position;
				if (entityB.Has<ParentComponent>()) {
					Entity parent = entityB.Get<ParentComponent>().Parent;
					posB += parent.Get<TransformComponent>().Position;
				}
				hitboxB = colliderB.rect;
				hitboxB.x += static_cast<int>(posB.x);
				hitboxB.y += static_cast<int>(posB.y);




				//Check for collision:
				if (AABB(hitboxA, hitboxB)) {
					//Check if solid on solid collision needs to be resolved:
					if (colliderA.IsSold && colliderB.IsSold) {
						//Resolve solid collision:
						ResolveSolidCollision(entityA, transformA, hitboxA,
							                  entityB, transformB, hitboxB);
					}
					//Execute OnCollision functions for both entities involved:

					colliderA.OnCollision(entityA, entityB);
					colliderB.OnCollision(entityB, entityA);
				}		
				//*/
			}
		}
		//*/
	}
};

}//END namespace ProjectAlpha