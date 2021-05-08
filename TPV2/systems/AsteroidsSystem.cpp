#include "AsteroidsSystem.h"

void AsteroidsSystem::init() {
	auto* e = manager_->addEntity();
}

void AsteroidsSystem::addAsteroids(int n)
{
	auto aManager = manager_->getHandler<AsteroidsManager>();
	for (int i = 0; i < n; i++)
	{
		manager_->getComponent<AsteroidsManager>(aManager)->generaAsteroide();
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	auto aManager = manager_->getHandler<AsteroidsManager>();
	manager_->getComponent<AsteroidsManager>(a)->OnCollision(a);
	manager_->setActive(a, false);
	manager_->send(BulletAsteroidCollision(b, a));
}

void AsteroidsSystem::update() {
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		// Asteroide de tipo B
		if (manager_->getComponent<AsteroidType>(manager_->getHandler<GameManager>())->type() == 'b') {
			//FOLLOW-------------------------------------------------------------------------------
			auto* tr = manager_->getComponent<Transform>(manager_->getHandler<GameManager>());
			assert(tr != nullptr);

			auto* cazaTr = manager_->getComponent<Transform>(manager_->getHandler<MainHandler>());
			assert(cazaTr != nullptr);

			auto& p = tr->getPos();
			auto& v = tr->getVel();
			auto& q = cazaTr->getPos();

			v.set(v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f));
			//-------------------------------------------------------------------------------------
		}
		// Asteroide de tipo A
		if (manager_->getComponent<AsteroidType>(manager_->getHandler<GameManager>())->type() == 'a') {

		}
	}
}
