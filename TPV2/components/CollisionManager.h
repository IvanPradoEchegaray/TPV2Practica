#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "AsteroidsManager.h"
#include "State.h"

class CollisionManager : public Component {
public:
	CollisionManager() {
	}
	virtual ~CollisionManager() {
	}

	void init() override {
	}

	void update() override {
	}


private:
}
;
