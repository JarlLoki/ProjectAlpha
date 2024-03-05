#include "Bullet.h"

namespace Entities::Bullet {

namespace Scripts {

//---------------
//| BulletLogic |
//---------------
////////////////////////////////////////////////////////////////////////////////
// Logic script for the Bullet entity
// -Kills the bullet once it goes past the screen
////////////////////////////////////////////////////////////////////////////////
struct BulletLogic : public PA::Script {
	void OnUpdate() override {
		const auto& transform = m_entity.Get<Components::Transform>();

		//Remove bullet if its past the screen
		if (transform.Position.y + 50 < 0) {
			m_entity.Kill();
		}
	}
};
}//END namespace Scripts

//--------------
//| InitAssets |
//--------------
////////////////////////////////////////////////////////////////////////////////
// Initiates assets for the Bullet entity
////////////////////////////////////////////////////////////////////////////////
void InitAssets() {
PA::Game::ImageAssets.LoadImageFromFile(Graphics::Bullet);
}

//----------
//| Create |
//----------
////////////////////////////////////////////////////////////////////////////////
// Creates a Bullet Entity
// -Takes a pointer to the scene that will be creating it and add its to the
// entity Registery of that scene
// -Returns the created Entity as well
////////////////////////////////////////////////////////////////////////////////
PA::Entity Create(PA::Scene* scene) {
	auto entity = scene->CreateEntity(Bullet::Name);
	entity.Add<Components::Transform>();
	entity.Add<Components::Physics>();

	auto& sprite = entity.Add<Components::Sprite>();
	sprite.Sprite.SpriteSheet = Graphics::Bullet;
	sprite.DrawLayer = 60;

	auto& collider = entity.Add<Components::Collider>();
	collider.Tag = Bullet::Name;
	collider.rect = PA::GetBindingBox(Graphics::Bullet);
	collider.IsSold = false;

	auto& scripts = entity.Add<Components::Script>(entity);
	scripts.Add<Scripts::BulletLogic>();

	return entity;
}

}//END namespace Entities::Bullet 