﻿#pragma once
#include "../ecs/System.h"
#include"../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
class FighterGunSystem : public System
{
public:
	// - si el juego está parado no hacer nada. Si el jugador pulsa SDLK_S, llamar
	// a shoot del BulletsSystem para añadir una bala al juego, etc.
	// - se puede incluir ese comportamiento en el FighterSystem directamente en
	// lugar de definirlo en un sistema separado
	void update() override;

};

