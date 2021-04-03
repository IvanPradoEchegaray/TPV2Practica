#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "Transform.h"
#include "AsteroidsManager.h"
#include "State.h"
#include "Health.h"
#include "../utils/Collisions.h"

class CollisionManager : public Component {
public:
	CollisionManager(Entity* player) : player_(player) {}
	virtual ~CollisionManager() {
	}

	void init() override {
	}

	void update() override {
		for (int i = 0; i < entity_->getMngr()->getEntities().size(); i++) {
			if (entity_->getMngr()->getEntities()[i]->hasGroup<Asteroid_grp>() && entity_->getMngr()->getEntities()[i]->isActive()) {
				//Asteroide activo
				Entity* asteroid = entity_->getMngr()->getEntities()[i];
				Transform* asteroid_tr = asteroid->getComponent<Transform>();
				//Si hay choque con el caza
				Transform* player_tr = player_->getComponent<Transform>();
				if (Collisions::collidesWithRotation(asteroid_tr->getPos(), asteroid_tr->getW(), asteroid_tr->getH(), asteroid_tr->getRot(),
					player_tr->getPos(), player_tr->getW(), player_tr->getH(), player_tr->getRot()))
					resetAll();

				//Balas activas
				for (int j = 0; j < entity_->getMngr()->getEntities().size(); j++) {
					if (entity_->getMngr()->getEntities()[j]->hasGroup<Bullet_grp>() && entity_->getMngr()->getEntities()[j]->isActive()) {
						Entity* bullet = entity_->getMngr()->getEntities()[j];
						Transform* bullet_tr = bullet->getComponent<Transform>();
						if (Collisions::collidesWithRotation(bullet_tr->getPos(), bullet_tr->getW(), bullet_tr->getH(), bullet_tr->getRot(),
							asteroid_tr->getPos(), asteroid_tr->getW(), asteroid_tr->getH(), asteroid_tr->getRot())) {
							bullet->setActive(false);
							AsteroidsManager* mngr_asteroids = entity_->getComponent<AsteroidsManager>();
							mngr_asteroids->OnCollision(asteroid);
							if (mngr_asteroids->getNumAsteroides() < 1) resetAll();
						}
					}
				}
			}
		}
	}
	void resetAll() {
		player_->getComponent<Health>()->loseLife();
		//Desactivar asteroides y balas
		for (Entity* e : entity_->getMngr()->getEntities()) {
			if (e->hasGroup<Asteroid_grp>() || e->hasGroup<Bullet_grp>())
				e->setActive(false);
		}
		//Si no le quedan vidas al player
		if (player_->getComponent<Health>()->isDead()) {
			entity_->getComponent<State>()->gameOver();
			player_->getComponent<Health>()->resetLifes();
		}
		else
			entity_->getComponent<State>()->pause();
	

		//Reset de la posicion del player
		Transform* player_tr = player_->getComponent<Transform>();
		//Posicion
		auto& player_pos = player_tr->getPos();
		player_pos.setX(sdlutils().width() / 2.0f - 20);
		player_pos.setY(sdlutils().height() / 2.0f - 20);
		//Rotacion
		player_tr->setRot(0);
		//Velocidad
		auto& player_vel = player_tr->getVel();
		player_vel.setX(0);
		player_vel.setY(0);
	}

private:
	Entity* player_;
}
;
