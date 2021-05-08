#include "BulletsSystem.h"

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	//Bala
	Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(vel.angle(Vector2D(0.0f, -1.0f)) * (vel.magnitude() + 5.0f));
	Vector2D bPos = pos + Vector2D(width / 2.0f, height / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(vel.angle(Vector2D(0.0f, -1.0f)));
	auto* bala = manager_->addEntity();
	manager_->addComponent<Transform>(bala,bPos, bVel, 5.0f, 20.f, vel.angle(Vector2D(0.0f, -1.0f)));
	manager_->addComponent<Image>(bala,&sdlutils().images().at("fire"));
	manager_->addComponent<DisableOnExit>(bala);
	manager_->setGroup<Bullet_grp>(bala, true);
	//Sonido a reproducir
	sdlutils().soundEffects().at("fire").play();
}

void BulletsSystem::onCollisionWithAsteroid(Entity* b, Entity* a)
{
	manager_->setActive(b, false);
}

void BulletsSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		for (Entity* b : manager_->getEntities()) {
			if (manager_->hasGroup<Bullet_grp>(b)) {
				manager_->getComponent<Transform>(b)->update();
				manager_->getComponent<DisableOnExit>(b)->update();
			}
		}
	}
}
