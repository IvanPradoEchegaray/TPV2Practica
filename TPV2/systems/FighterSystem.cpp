#include "FighterSystem.h"
#include "NetworkSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	//Reset de la posicion del player1
	Transform* player1_tr = manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>());
	//Posicion
	player1_tr->getPos().setX(sdlutils().width() / 2.0f - 20);
	player1_tr->getPos().setY(sdlutils().height() / 2.0f - 20);
	//Rotacion
	player1_tr->setRot(0);
	//Velocidad
	auto& player1_vel = player1_tr->getVel();
	player1_vel.setX(0);
	player1_vel.setY(0);
	//Aviso al gamectrlsystem
	manager_->getSystem<GameCtrlSystem>()->onFighterDeath();


	//Reset de la posicion del player2
	Transform* player2_tr = manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>());
	//Posicion
	player2_tr->getPos().setX(sdlutils().width() / 2.0f - 20);
	player2_tr->getPos().setY(sdlutils().height() / 2.0f - 20);
	//Rotacion
	player2_tr->setRot(0);
	//Velocidad
	auto& player2_vel = player2_tr->getVel();
	player2_vel.setX(0);
	player2_vel.setY(0);
	//Aviso al gamectrlsystem
	manager_->getSystem<GameCtrlSystem>()->onFighterDeath();
}

void FighterSystem::init()
{
	//Player1
	player1 = manager_->addEntity();
	manager_->addComponent<Transform>(player1,
		Vector2D(sdlutils().width() / 10.0f - 20, sdlutils().height() / 2.0f - 20),
		Vector2D(0.0f, 0.0f), 40.0f, 40.0f, 0.0f);
	manager_->addComponent<Image>(player1, &sdlutils().images().at("fighter"), manager_->getComponent<Transform>(player1));
	manager_->addComponent<DeAcceleration>(player1, manager_->getComponent<Transform>(player1));
	manager_->addComponent<Health>(player1, 3,
		Vector2D(sdlutils().width() * 0.02f, sdlutils().height() * 0.02f), 40.0f, 40.0f,
		&sdlutils().images().at("heart"));
	manager_->addComponent<FighterCtrl>(player1, manager_->getComponent<Transform>(player1));
	manager_->addComponent<ShowAtOppositeSide>(player1, manager_->getComponent<Transform>(player1));
	manager_->setHandler<Player1Handler>(player1);

	//Player2
	player2 = manager_->addEntity();
	manager_->addComponent<Transform>(player2,
		Vector2D(sdlutils().width() / 10.0f * 9 - 20, sdlutils().height() / 2.0f - 20),
		Vector2D(0.0f, 0.0f), 40.0f, 40.0f, 0.0f);
	manager_->addComponent<Image>(player2,&sdlutils().images().at("fighter2"), manager_->getComponent<Transform>(player2));
	manager_->addComponent<DeAcceleration>(player2, manager_->getComponent<Transform>(player2));
	manager_->addComponent<Health>(player2,3,
		Vector2D(sdlutils().width() * 0.02f, sdlutils().height() * 0.02f), 40.0f, 40.0f,
		&sdlutils().images().at("heart"));
	manager_->addComponent<FighterCtrl>(player2, manager_->getComponent<Transform>(player2));
	manager_->addComponent<ShowAtOppositeSide>(player2, manager_->getComponent<Transform>(player2));
	manager_->setHandler<Player2Handler>(player2);
}

void FighterSystem::update()
{
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		playerId_ = manager_->getSystem<NetworkSystem>()->getId();

		// Updates que no se basan en manejo de player
		manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>())->update();
		manager_->getComponent<DeAcceleration>(manager_->getHandler<Player1Handler>())->update();
		manager_->getComponent<ShowAtOppositeSide>(manager_->getHandler<Player1Handler>())->update();
		manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>())->update();
		manager_->getComponent<DeAcceleration>(manager_->getHandler<Player2Handler>())->update();
		manager_->getComponent<ShowAtOppositeSide>(manager_->getHandler<Player2Handler>())->update();

		// Controladores de input de cada uno de los jugadores
		if (playerId_ == 0) {
			manager_->getComponent<FighterCtrl>(manager_->getHandler<Player1Handler>())->update();
			if (ih().keyDownEvent()) {
				if (ih().isKeyDown(SDLK_s) && manager_->getComponent<FighterCtrl>(manager_->getHandler<Player1Handler>())->inputIsEnabled()) {
					manager_->getSystem<FighterSystem>()->shootBullet();
				}
			}
		}
		else if (playerId_ == 1) {
			manager_->getComponent<FighterCtrl>(manager_->getHandler<Player2Handler>())->update();
			if (ih().keyDownEvent()) {
				if (ih().isKeyDown(SDLK_s) && manager_->getComponent<FighterCtrl>(manager_->getHandler<Player2Handler>())->inputIsEnabled()) {
					manager_->getSystem<FighterSystem>()->shootBullet();
				}
			}
		}
	}
}

void FighterSystem::shootBullet()
{
	Uint32 currentTime = sdlutils().currRealTime() - startTime_;
	if (currentTime >= 250) {
		Transform* player_tr = nullptr;
		if (playerId_ == 0)
			player_tr = manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>());
		else
			player_tr = manager_->getComponent<Transform>(manager_->getHandler<Player2Handler>());

		manager_->getSystem<BulletsSystem>()->shoot(player_tr->getPos(),player_tr->getVel(),player_tr->getW(), player_tr->getH());
		startTime_ = sdlutils().currRealTime();
	}
}

void FighterSystem::setFighterPosition(Uint8 playerId, Vector2D pos)
{
	Entity* e = nullptr;
	if (playerId == 0)
		e = player1;
	else
		e = player2;

	manager_->getComponent<Transform>(e)->getPos().set(pos);
}
