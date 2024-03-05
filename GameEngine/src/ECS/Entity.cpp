#include "Entity.h"

#include "Components/Components.h"

namespace ProjectAlpha { 

Entity::Entity(entt::entity handle, Scene* scene) 
	: m_entityHandle(handle), m_scene(scene) {}

void Entity::Kill() {
	if(!Has<DestroyFlag>())
		Add<DestroyFlag>();
}


}//END namespace ProjectAlpha
