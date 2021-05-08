#include "FighterGunSystem.h"

void FighterGunSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		manager_->getSystem<FighterSystem>()->shootBullet();
	}
}
