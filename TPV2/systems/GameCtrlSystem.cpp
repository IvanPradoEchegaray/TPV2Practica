#include "GameCtrlSystem.h"
#include "NetworkSystem.h"
#include "FighterSystem.h"

void GameCtrlSystem::onFighterDeath(Side side) {
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEnteties()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}
	/*
	manager_->getComponent<Health>(manager_->getHandler<Player1Handler>())->loseLife();
	if (manager_->getComponent<Health>(manager_->getHandler<Player1Handler>())->isDead()) {
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(GAMEOVER);
		manager_->getComponent<Health>(manager_->getHandler<Player1Handler>())->resetLifes();
	}
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(PAUSED);*/
	assert(getGameState() == RUNNING); // this should be called only when game is runnig

	if (side == LEFT) {
		score_[1]++;
	}
	else {
		score_[0]++;
	}

	if (score_[0] < maxScore_ && score_[1] < maxScore_)
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(PAUSED);
	else
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(GAMEOVER);

	manager_->getSystem<NetworkSystem>()->sendStateChanged(getGameState(), score_[0],
		score_[1]);
}

void GameCtrlSystem::onAsteroidsExtinction() {
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEnteties()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}

	manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(GAMEOVER);
	manager_->getComponent<Health>(manager_->getHandler<Player1Handler>())->resetLifes();
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(PAUSED);
}

Uint8 GameCtrlSystem::getGameState() {
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
			manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(RUNNING);
			//Crea 10 asteroides
			//manager_->getSystem<AsteroidsSystem>()->addAsteroids(10);
		}
		else if (ih().isKeyDown(SDL_SCANCODE_P)) {
			manager_->getSystem<NetworkSystem>()->switchId();
		}
	}
	//Desactvar input en start, pausa y gameover
	if (manager_->getComponent<State>(manager_->getHandler<GameManager>())->getState() != RUNNING) {
		manager_->getComponent<FighterCtrl>(manager_->getHandler<Player1Handler>())->enableInput(false);
		manager_->getComponent<FighterCtrl>(manager_->getHandler<Player2Handler>())->enableInput(true);
	}
	else {
		manager_->getComponent<FighterCtrl>(manager_->getHandler<Player1Handler>())->enableInput(true);
		manager_->getComponent<FighterCtrl>(manager_->getHandler<Player2Handler>())->enableInput(true);
	}
}

void GameCtrlSystem::startGame()
{
	if (getGameState() == RUNNING)
		return;

	if (!manager_->getSystem<NetworkSystem>()->isGameReady())
		return;

	auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();

	if (isMaster) {
		manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(RUNNING);
		//manager_->getSystem<BallSystem>()->initBall();
		manager_->getSystem<NetworkSystem>()->sendStateChanged(getGameState(),
			score_[0], score_[1]);
	}
	else {
		manager_->getSystem<NetworkSystem>()->sendStartGameRequest();
	}
}

void GameCtrlSystem::changeState(Uint8 state, Uint8 left_score, Uint8 right_score)
{
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(state);
	score_[0] = left_score;
	score_[1] = right_score;
}

void GameCtrlSystem::resetGame()
{
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->changeState(NEWGAME);
	score_[0] = score_[1] = 0;
	//Desactivar asteroides y balas
	for (Entity* e : manager_->getEnteties()) {
		if (manager_->hasGroup<Bullet_grp>(e))
			manager_->setActive(e, false);
	}
	manager_->getSystem<FighterSystem>()->resetFighters();
}
