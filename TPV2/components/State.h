#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

enum state : Uint8 { NEWGAME = 0, PAUSED, RUNNING, GAMEOVER };
class State : public Component {
public:
	State() {
		startRect = &sdlutils().images().at("start");
		continueRect = &sdlutils().images().at("continue");
		gameOverRect = &sdlutils().images().at("gameover");
		currentState = NEWGAME;
	}
	virtual ~State() {}

	void render() {
		Vector2D pos = Vector2D(sdlutils().width() * 0.5f - 175, sdlutils().height() * 0.65f);
		if (currentState == NEWGAME) {
			SDL_Rect dest = build_sdlrect(pos, startRect->width(), startRect->height());
			startRect->render(dest, 0);
		}
		else if (currentState == PAUSED) {
			SDL_Rect dest = build_sdlrect(pos, continueRect->width(), continueRect->height());
			continueRect->render(dest, 0);
		}
		else if (currentState == GAMEOVER) {
			Vector2D gO_pos = Vector2D(sdlutils().width() * 0.5f - 175, sdlutils().height() * 0.35f); 
			SDL_Rect gO_dest = build_sdlrect(gO_pos, gameOverRect->width(), gameOverRect->height());
			gameOverRect->render(gO_dest, 0);
			SDL_Rect dest = build_sdlrect(pos, startRect->width(), startRect->height());
			startRect->render(dest, 0);
		}

	}
	
	void changeState(state state) { currentState = state; }
	void changeState(Uint8 state) { currentState = state; }

	const Uint8& getState() { return currentState; }

private:
	Texture* startRect, *continueRect, *gameOverRect;
	Uint8 currentState;
}
;


