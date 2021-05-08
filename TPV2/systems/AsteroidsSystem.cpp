#include "AsteroidsSystem.h"

void AsteroidsSystem::addAsteroids(int n)
{
	for (int i = 0; i < n; i++)
	{
		manager_->getComponent<AsteroidsManager>()->generaAsteroide();
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	manager_->getComponent<AsteroidsManager>(a)->OnCollision(a);
	if (manager_->getComponent<AsteroidsManager>()->getNumAsteroides <= 0)
	{
		manager_->getSystem<GameCtrlSystem>()->onAsteroidsExtinction();
	}
}

void AsteroidsSystem::update()
{
}
