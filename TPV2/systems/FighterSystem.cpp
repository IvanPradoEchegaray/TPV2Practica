#include "FighterSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a)
{
	//Reset de la posicion del player
	Transform* player_tr = manager_->getComponent<Transform>(a);
	//Posicion
	player_tr
	player_tr->getPos().setX(sdlutils().width() / 2.0f - 20);
	player_pos.setY(sdlutils().height() / 2.0f - 20);
	//Rotacion
	player_tr->setRot(0);
	//Velocidad
	auto& player_vel = player_tr->getVel();
	player_vel.setX(0);
	player_vel.setY(0);
}
