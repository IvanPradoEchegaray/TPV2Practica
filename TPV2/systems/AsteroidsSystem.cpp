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
	if (manager_->getComponent<AsteroidsManager>(aManager)->getNumAsteroides() <= 0)
	{
		manager_->getSystem<GameCtrlSystem>()->onAsteroidsExtinction();
	}
}

void AsteroidsSystem::update()
{
}
