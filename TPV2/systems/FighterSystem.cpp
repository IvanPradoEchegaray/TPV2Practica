#include "FighterSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	//Reset de la posicion del player
	Transform* player_tr = manager_->getComponent<Transform>(manager_->getHandler<MainHandler>());
	//Posicion
	player_tr->getPos().setX(sdlutils().width() / 2.0f - 20);
	player_tr->getPos().setY(sdlutils().height() / 2.0f - 20);
	//Rotacion
	player_tr->setRot(0);
	//Velocidad
	auto& player_vel = player_tr->getVel();
	player_vel.setX(0);
	player_vel.setY(0);
	//Aviso al gamectrlsystem
	manager_->send(FighterAsteroidCollision(manager_->getHandler<MainHandler>(), a));
}

void FighterSystem::init()
{
	//Player Entidad
	auto* player = manager_->addEntity();
	manager_->addComponent<Transform>(player,
		Vector2D(sdlutils().width() / 2.0f - 20, sdlutils().height() / 2.0f - 20),
		Vector2D(0.0f, 0.0f), 20.0f, 20.0f, 0.0f);
	manager_->addComponent<Image>(player,&sdlutils().images().at("fighter"), manager_->getComponent<Transform>(player));
	manager_->addComponent<DeAcceleration>(player, manager_->getComponent<Transform>(player));
	manager_->addComponent<Health>(player,3,
		Vector2D(sdlutils().width() * 0.02f, sdlutils().height() * 0.02f), 40.0f, 40.0f,
		&sdlutils().images().at("heart"));
	manager_->addComponent<FighterCtrl>(player, manager_->getComponent<Transform>(player));
	manager_->addComponent<ShowAtOppositeSide>(player, manager_->getComponent<Transform>(player));
	manager_->setHandler<MainHandler>(player);
}

void FighterSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		manager_->getComponent<DeAcceleration>(manager_->getHandler<MainHandler>())->update();
		manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->update();
		manager_->getComponent<ShowAtOppositeSide>(manager_->getHandler<MainHandler>())->update();
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_s) && manager_->getComponent<FighterCtrl>(manager_->getHandler<MainHandler>())->inputIsEnabled()) {
				manager_->getSystem<FighterSystem>()->shootBullet();
			}
		}
	}
}

void FighterSystem::shootBullet()
{
	Uint32 currentTime = sdlutils().currRealTime() - startTime_;
	if (currentTime >= 250) {
		Transform* player_tr = manager_->getComponent<Transform>(manager_->getHandler<MainHandler>());
		manager_->getSystem<BulletsSystem>()->shoot(player_tr->getPos(),player_tr->getVel(),player_tr->getW(), player_tr->getH());
		startTime_ = sdlutils().currRealTime();
	}
}
