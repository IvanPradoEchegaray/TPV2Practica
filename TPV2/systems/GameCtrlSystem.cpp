#include "GameCtrlSystem.h"

void GameCtrlSystem::onFighterDeath() {
	manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->loseLife();
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEntities()) {
		if (manager_->hasGroup<Asteroid_grp>(e) || manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}
	//Si no le quedan vidas al player
	if (manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->isDead()) {
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->gameOver();
		manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->resetLifes();
	}
	else
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->pause();
}

void GameCtrlSystem::onAsteroidsExtinction() {
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEntities()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}

	manager_->getComponent<State>(manager_->getHandler<GameManager>())->gameOver();
	manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->resetLifes();
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->pause();
}

state GameCtrlSystem::getGameState() {
	return manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState();
}

void GameCtrlSystem::init()
{
	auto* gameManager = manager_->addEntity();
	manager_->addComponent<State>(gameManager);
	manager_->addComponent<GameCtrl>(gameManager, manager_->getHandler<MainHandler>());
	manager_->addComponent<AsteroidsManager>(gameManager, manager_->getHandler<MainHandler>());
	manager_->addComponent<CollisionManager>(gameManager, manager_->getHandler<MainHandler>());
	manager_->setHandler<GameManager>(gameManager);
}

void GameCtrlSystem::update()
{
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDLK_SPACE) && manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState() != RUNNING) {
			manager_->getComponent<State>(manager_->getHandler<GameManager>())->run();
			//Crea 10 asteroides
			for (int i = 0; i < 10; i++)
				manager_->getComponent<AsteroidsManager>(manager_->getHandler<GameManager>())->generaAsteroide();

		}
	}
	//Desactvar input en start, pausa y gameover
	if (manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState() != RUNNING)
		manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->enableInput(false);
	else
		manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->enableInput(true);
}
