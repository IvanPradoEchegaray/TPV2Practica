
#include "RenderSystem.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/SDLUtils.h"
#include "GameCtrlSystem.h"
#include "NetworkSystem.h"

RenderSystem::RenderSystem() :
	player1Tr_(nullptr), //
	player2Tr_(nullptr) {
}

RenderSystem::~RenderSystem() {
}

void RenderSystem::init() {
	player1Tr_ = manager_->getComponent<Transform>(
		manager_->getHandler<Player1Handler>());
	assert(player1Tr_ != nullptr);
	player2Tr_ = manager_->getComponent<Transform>(
		manager_->getHandler<Player2Handler>());
	assert(player2Tr_ != nullptr);
}

void RenderSystem::update() {
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		for (Entity* e : manager_->getEnteties()) {
			if (manager_->hasGroup<Bullet_grp>(e))
				manager_->getComponent<Image>(e)->render();
		}
	}
	manager_->getComponent<Image>(manager_->getHandler<Player1Handler>())->render();
	manager_->getComponent<Image>(manager_->getHandler<Player2Handler>())->render();

	drawScore();
	drawMsgs();
	drawNames();
}

void RenderSystem::drawScore() {

	auto& score_ = manager_->getSystem<GameCtrlSystem>()->getScore();
	// score
	Texture scoreMsg(
		sdlutils().renderer(), //
		std::to_string(score_[0]) + " - " + std::to_string(score_[1]),
		sdlutils().fonts().at("ARIAL16"), build_sdlcolor(0xffffffff));
	scoreMsg.render((sdlutils().width() - scoreMsg.width()) / 2, 10);
}

void RenderSystem::drawMsgs() {
	manager_->getComponent<State>(manager_->getHandler<GameManager>())->render();
}

void RenderSystem::drawNames() {
	auto& names_ = manager_->getSystem<NetworkSystem>()->getNames();

	// name of player 0
	Texture name_0(
		sdlutils().renderer(), //
		names_[0], sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	name_0.render(10, 10);

	// name of player 1
	Texture name_1(
		sdlutils().renderer(), //
		names_[1], sdlutils().fonts().at("ARIAL16"),
		build_sdlcolor(0xffffffff));
	name_1.render(sdlutils().width() - name_1.width() - 10, 10);

	// draw a star next to the master name
	auto isMaster = manager_->getSystem<NetworkSystem>()->isMaster();
	auto myId = manager_->getSystem<NetworkSystem>()->getId();

	Texture isMasterMsg(sdlutils().renderer(), //
		"*", //
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0xff0000ff));
	isMasterMsg.render(
		(isMaster && myId == 1) || (!isMaster && myId == 0) ?
		sdlutils().width() - isMasterMsg.width() - 1 : 1, 10);

}
