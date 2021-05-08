#include "CollisionsSystem.h"

void CollisionSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {

		//check if bullets or fighter hits asteroids
		if (Collisions::collides(asteroidTr_->getPos(), asteroidTr_->getW(), asteroidTr_->getH(),
			tr->getPos(), tr->getW(), tr->getH()))
		{

		}
		for (auto& e : manager_->getEntities()) {
			if (manager_->hasGroup<Generations>(e)) {
				auto tr = manager_->getComponent<Transform>(e);

				if (Collisions::collides(asteroidTr_->getPos(), asteroidTr_->getW(), asteroidTr_->getH(),
					tr->getPos(), tr->getW(), tr->getH()))
				{
					manager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(manager_->getHandler<Generations>());
				}
			}
		}
	}
}
