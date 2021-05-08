#include "RenderSystem.h"

void RenderSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		for (Entity* e : manager_->getEntities()) {
			if (manager_->hasGroup<Bullet_grp>(e) || manager_->hasGroup<Bullet_grp>(e)) {
				if (manager_->hasComponent<FramedImage>(e))
					manager_->getComponent<FramedImage>(e)->render();
				else if(manager_->hasComponent<Image>(e))
					manager_->getComponent<Image>(e)->render();
			}
		}
		manager_->getComponent<Image>(manager_->getHandler<MainHandler>())->render();
	}
	manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->render();
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->render();
}
