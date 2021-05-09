#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class Generations: public Component {
public:
	Generations(Transform* tr) : tr_(tr), gen_(sdlutils().rand().nextInt(1, 4)) {}
	Generations(Transform* tr, int i) : tr_(tr), gen_(i) {}

	virtual ~Generations() {}

	void init() {
	    assert(tr_ != nullptr);

		tr_->setH(14.0f + 7.0f * gen_);
		tr_->setW(14.0f + 7.0f * gen_);
	}

	int getGenerations() {
		return gen_;
	}

private:
	Transform* tr_;
	float gen_;
};