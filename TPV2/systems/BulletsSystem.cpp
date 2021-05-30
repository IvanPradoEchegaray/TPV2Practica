#include "BulletsSystem.h"
#include "NetworkSystem.h"

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	Uint8 playerId = manager_->getSystem<NetworkSystem>()->getId();

	//Bala
	if (playerId == 0)
	{
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate
		(manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>())->getRot()) * (vel.magnitude() + 5.0f);

		Vector2D bPos = pos + Vector2D(width / 2.0f, height / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate
		(manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>())->getRot())- Vector2D(2.0,10.0f);

		auto* bala = manager_->addEntity();
		manager_->addComponent<Transform>(bala,bPos, bVel, 5.0f, 20.f, manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>())->getRot());
		manager_->addComponent<Image>(bala,&sdlutils().images().at("fire"), manager_->getComponent<Transform>(bala));
		manager_->addComponent<DisableOnExit>(bala, manager_->getComponent<Transform>(bala), manager_, bala);
		manager_->setGroup<Bullet_grp>(bala, true);
	}
	else {
		Vector2D bVel = Vector2D(0.0f, -1.0f).rotate
		(manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>())->getRot()) * (vel.magnitude() + 5.0f);

		Vector2D bPos = pos + Vector2D(width / 2.0f, height / 2.0f) - Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate
		(manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>())->getRot()) - Vector2D(2.0, 10.0f);

		auto* bala = manager_->addEntity();
		manager_->addComponent<Transform>(bala, bPos, bVel, 5.0f, 20.f, manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>())->getRot());
		manager_->addComponent<Image>(bala, &sdlutils().images().at("fire"), manager_->getComponent<Transform>(bala));
		manager_->addComponent<DisableOnExit>(bala, manager_->getComponent<Transform>(bala), manager_, bala);
		manager_->setGroup<Bullet_grp>(bala, true);
	}
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
		for (Entity* b : manager_->getEnteties()) {
			if (manager_->hasGroup<Bullet_grp>(b)) {
				manager_->getComponent<Transform>(b)->update();
				manager_->getComponent<DisableOnExit>(b)->update();
			}
		}
	}
}

void BulletsSystem::setBulletInfo(Vector2D pos, Vector2D vel, double width, double height)
{
	manager_->getComponent<Transform>(manager_->getHandler<GameManager>())->getPos().set(pos);
	manager_->getComponent<Transform>(manager_->getHandler<GameManager>())->getVel().set(vel);
	manager_->getComponent<Transform>(manager_->getHandler<GameManager>())->setW(width);
	manager_->getComponent<Transform>(manager_->getHandler<GameManager>())->setH(height);
}
