// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class Rotate : public Component {
public:
	Rotate(Transform* tr) :
		tr_(tr) {
	}
	virtual ~Rotate() {
	}

	void update() {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_LEFT)) 
			{
				tr_->setRot(tr_->getRot() - 5.0f);

			}
			else if (ih().isKeyDown(SDLK_RIGHT))
			{
				tr_->setRot(tr_->getRot() + 5.0f);
			}
		}
	}

private:
	Transform* tr_;
}
;