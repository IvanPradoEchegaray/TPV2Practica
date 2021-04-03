#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
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
			if (ih().isKeyDown(SDLK_SPACE) && entity_->getComponent<State>()->getState() != RUNNING) {
				entity_->getComponent<State>()->run();
				//Crea 10 asteroides
				for (int i = 0; i < 10; i++)
					entity_->getComponent<AsteroidsManager>()->generaAsteroide();
				
			}
		}

	}


private:
}
;