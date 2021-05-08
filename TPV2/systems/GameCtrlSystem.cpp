#include "GameCtrlSystem.h"

void GameCtrlSystem::onFighterDeath() {

}

void GameCtrlSystem::onAsteroidsExtinction()
{
}

state GameCtrlSystem::getGameState()
{
	game = manager_->getComponent<State>();
	state gameState = State::getState();
	return state();
}

void GameCtrlSystem::init()
{
}

void GameCtrlSystem::update()
{
}
