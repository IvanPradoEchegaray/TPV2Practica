#include "CollisionsSystem.h"

void CollisionSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		for (int i = 0; i < manager_->getEntities().size(); i++) {
			if (manager_->hasGroup<Asteroid_grp>(manager_->getEntities()[i]) && manager_->isActive(manager_->getEntities()[i])) {
				//Asteroide activo
				Entity* asteroid = manager_->getEntities()[i];
				Transform* asteroid_tr = manager_->getComponent<Transform>(asteroid);
				//Si hay choque con el caza
				Transform* player_tr = manager_->getComponent<Transform>(manager_->getHandler<MainHandler>());
				if (Collisions::collidesWithRotation(asteroid_tr->getPos(), asteroid_tr->getW(), asteroid_tr->getH(), asteroid_tr->getRot(),
					player_tr->getPos(), player_tr->getW(), player_tr->getH(), player_tr->getRot())) {
					manager_->getSystem<GameCtrlSystem>()->onFighterDeath();
					//Sonido a reproducir
					sdlutils().soundEffects().at("explosion").play();
				}

				//Balas activas
				for (int j = 0; j < manager_->getEntities().size(); j++) {
					if (manager_->hasGroup<Bullet_grp>(manager_->getEntities()[i]) && manager_->isActive(manager_->getEntities()[i])) {
						Entity* bullet = manager_->getEntities()[j];
						Transform* bullet_tr = manager_->getComponent<Transform>(manager_->getHandler<GameManager>());
						if (Collisions::collidesWithRotation(bullet_tr->getPos(), bullet_tr->getW(), bullet_tr->getH(), bullet_tr->getRot(),
							asteroid_tr->getPos(), asteroid_tr->getW(), asteroid_tr->getH(), asteroid_tr->getRot())) {
							//Sonido a reproducir
							sdlutils().soundEffects().at("bangSmall").play();
							manager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(asteroid, bullet);
							if (manager_->getComponent<AsteroidsManager>(manager_->getHandler<GameManager>())->getNumAsteroides() < 1)
								manager_->getSystem<GameCtrlSystem>()->onAsteroidsExtinction();
						}
					}
				}
			}
		}
	}
}
