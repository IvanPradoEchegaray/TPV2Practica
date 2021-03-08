#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Generations: public Component {
public:
	Generations() : tr_(nullptr), gen_(sdlutils().rand().nextInt(0, 3)) {}

	virtual ~Generations() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
	    assert(tr_ != nullptr);

		tr_->setH(10.0f + 5.0f * gen_);
		tr_->setW(10.0f + 5.0f * gen_);
	}

	void update() override {

	}

private:
	Transform* tr_;
	float gen_;
};