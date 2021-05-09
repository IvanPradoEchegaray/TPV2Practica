#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DeAcceleration : public Component {
public:
	DeAcceleration(Transform* tr) :
		tr_(tr) {
	}
	virtual ~DeAcceleration() {
	}

	void update() {
		auto& vel = tr_->getVel();
		vel = vel * 0.995f;
	}

private:
	Transform* tr_;
};