#pragma once
#include "../ecs/System.h"
#include "../components/State.h"
#include "../components/Health.h"
#include "../sdlutils/InputHandler.h"
#include "../components/AsteroidsManager.h"
#include "../components/FighterCtrl.h"
#include "../sdlutils/Messages.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"


class GameCtrlSystem : public System
{
public:
	enum Side {
		LEFT = 0, //
		RIGHT
	};
	GameCtrlSystem();
	// - a este mÈtodo se le va a llamar cuando muere el caza.
	// - desactivar los asteroides y las balas, actualizar el estado del juego, etc.
	void onFighterDeath(Side side);
	// - a este mÈtodo se le va a llamar cuando no haya m·s asteroides.
	// - desactivar todas las balas, etc.
	void onAsteroidsExtinction();
	// - devuelve el estado del juego.
	Uint8 getGameState();
	// - inicializar el estado del juego si es necesario, etc.
	void init() override;
	// - si el juego estÅEparado y el jugador pulsa SDLK_SPACE cambia el estado como
	// en la pr·ctica 1, etc.
	void update() override;
	//Score
	const auto& getScore() {
		return score_;
	}
	void resetScore();
	//Messages
	void startGame();
	void changeState(Uint8 state, Uint8 left_score, Uint8 right_score);
	void resetGame();

private:
	std::array<Uint8, 2> score_;
	Uint8 maxScore_;
};