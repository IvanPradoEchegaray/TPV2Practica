#include "GameCtrlSystem.h"

void GameCtrlSystem::onFighterDeath()
{
}

void GameCtrlSystem::onAsteroidsExtinction()
{
}

state GameCtrlSystem::getGameState()
{
	return state();
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
}
