#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Generations: public Component {
public:
	Generations() : tr_(nullptr), gen_(sdlutils().rand().nextInt(1, 4)) {}

	virtual ~Generations() {}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
	    assert(tr_ != nullptr);

		tr_->setH(20.0f + 10.0f * gen_);
		tr_->setW(20.0f + 10.0f * gen_);
	}
private:
	Transform* tr_;
	float gen_;
};