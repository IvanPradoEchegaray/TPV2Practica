#include "GameCtrlSystem.h"

void GameCtrlSystem::onFighterDeath() {
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroid_grp>(e) || manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}
	manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->loseLife();
	if (manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->isDead()) {
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->gameOver();
		manager_->getComponent<Health>(manager_->getHandler<MainHandler>())->resetLifes();
	}
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->pause();
}

void GameCtrlSystem::onAsteroidsExtinction() {
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEnteties()) {
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
	//manager_->addComponent<GameCtrl>(gameManager, manager_->getHandler<MainHandler>());
	//manager_->addComponent<AsteroidsManager>(gameManager, manager_->getHandler<MainHandler>());
	//manager_->addComponent<CollisionManager>(gameManager, manager_->getHandler<MainHandler>());
	manager_->setHandler<GameManager>(gameManager);
}

void GameCtrlSystem::update()
{
	if (ih().keyDownEvent()) {
		if (ih().isKeyDown(SDLK_SPACE) && manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState() != RUNNING) {
			manager_->getComponent<State>(manager_->getHandler<GameManager>())->run();
			//Crea 10 asteroides
			manager_->getSystem<AsteroidsSystem>()->addAsteroids(10);
		}
	}
	//Desactvar input en start, pausa y gameover
	if (manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState() != RUNNING)
		manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->enableInput(false);
	else
		manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->enableInput(true);
}

/*void GameCtrlSystem::receive(const Message& msg)
{
	switch (msg.id_)
	{
	case Fighter_Asteroid_Collision:
		const FighterAsteroidCollision& m = static_cast<const FighterAsteroidCollision&>(msg);
		manager_->getComponent<Health>(m.player_)->loseLife();
		if (manager_->getComponent<Health>(m.player_)->isDead())
			onFighterDeath();
		break;
	case Bullet_Asteroid_Collision:
		const BulletAsteroidCollision& ms = static_cast<const BulletAsteroidCollision&>(msg);
		manager_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(ms.asteroid_, ms.bullet_);
		manager_->getSystem<BulletsSystem>()->onCollisionWithAsteroid(ms.bullet_,ms.asteroid_);
		if (manager_->getSystem<AsteroidsSystem>()->getNumAsteroids() <= 0)
			onAsteroidsExtinction();
		break;
	}
}*/
