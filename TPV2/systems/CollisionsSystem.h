#pragma once
#include "GameCtrlSystem.h"
#include "AsteroidsSystem.h"
#include "FighterSystem.h"

#include "../ecs/System.h"
#include "../ecs/Entity.h"
#include "../components/Transform.h"
#include "../components/CollisionManager.h"

class CollisionSystem : public System {
public:
	// - si el juego estÅEparado no hacer nada.
	// - comprobar colisiones como en la pr·ctica 1 y avisar a los sistemas
	// correspondientes en caso de colisiones
	void update() override;
};