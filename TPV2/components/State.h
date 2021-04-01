#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

class State : public Component {
public:
	State() {
	}
	virtual ~State() {
	}

	void init() override {
	}

private:
}
;


