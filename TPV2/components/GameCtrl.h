#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "AsteroidsManager.h"
#include "State.h"

class GameCtrl : public Component {
public:
	GameCtrl() {
	}
	virtual ~GameCtrl() {
	}

	void init() override {
	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_SPACE)) {
				
			}
		}
	}


private:
	enum state { NEWGAME, PAUSED, RUNNING, GAMEOVER };
}
;
