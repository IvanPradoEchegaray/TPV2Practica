#include "CollisionsSystem.h"
#include "NetworkSystem.h"
#include "GameCtrlSystem.h"

void CollisionSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		Transform* player1tr = manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>());
		Transform* player2tr = manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>());
		//Balas activas
		for (int j = 0; j < manager_->getEnteties().size(); j++) {
			if (manager_->hasGroup<Bullet_grp>(manager_->getEnteties()[j]) && manager_->isActive(manager_->getEnteties()[j])) {
				Entity* bullet = manager_->getEnteties()[j];
				Transform* bullet_tr = manager_->getComponent<Transform>(bullet);

				//Colision con player 1
				if (Collisions::collidesWithRotation(bullet_tr->getPos(), bullet_tr->getW(), bullet_tr->getH(), bullet_tr->getRot(),
					player1tr->getPos(), player1tr->getW(), player1tr->getH(), player1tr->getRot())) 
				{
					//Sonido a reproducir
					sdlutils().soundEffects().at("bangSmall").play();
					manager_->getSystem<GameCtrlSystem>()->onFighterDeath(GameCtrlSystem::LEFT);
				}
				//Colision con player 2
				else if (Collisions::collidesWithRotation(bullet_tr->getPos(), bullet_tr->getW(), bullet_tr->getH(), bullet_tr->getRot(),
					player2tr->getPos(), player2tr->getW(), player2tr->getH(), player2tr->getRot())) 
				{
					//Sonido a reproducir
					sdlutils().soundEffects().at("bangSmall").play();
					manager_->getSystem<GameCtrlSystem>()->onFighterDeath(GameCtrlSystem::RIGHT);
				}
			}
		}
	}
}
