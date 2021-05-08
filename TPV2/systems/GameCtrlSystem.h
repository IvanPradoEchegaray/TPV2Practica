#pragma once
#include "../ecs/System.h"
#include "../components/State.h"
#include "../components/Health.h"
#include "../sdlutils/InputHandler.h"
#include "../components/AsteroidsManager.h"
#include "../components/FighterCtrl.h"
#include "../sdlutils/Messages.h"
#include "AsteroidsSystem.h"


class GameCtrlSystem : public System
{
public:
	// - a este m�todo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath();
	// - a este m�todo se le va a llamar cuando no haya m�s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	state getGameState();
	// - inicializar el estado del juego si es necesario, etc.
	void init() override;
	// - si el juego est�Eparado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr�ctica 1, etc.
	void update() override;

	void receive(const Message& msg) override;
};