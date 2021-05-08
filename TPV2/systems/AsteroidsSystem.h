#pragma once
#include "GameCtrlSystem.h"
#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/AsteroidsManager.h"

using namespace std;

class AsteroidsSystem : public System {
public:
	void init();
	// - aÒade n asteroides al juego como en la pr·ctica 1.
	void addAsteroids(int n);
	// - desactivar el asteroide ìaÅEy crear 2 asteroides como en la pr·ctica 1.
	// - pasamos una referencia a la bala aunque no se usa de momento (en el futuro
	// se puede usar para tener comportamientos distintos depende del tipo de
	// bala, etc.)
	// - si no hay m·s asteroides avisar al GameCtrlSystem
	void onCollisionWithBullet(Entity* a, Entity* b);
	// - si el juego estÅEparado no hacer nada.
	// - mover los asteroides como en la pr·ctica 1.
	void update() override;
private:
	size_t numOfAsteroids_;
};