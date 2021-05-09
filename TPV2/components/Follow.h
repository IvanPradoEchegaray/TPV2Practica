#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Rotate.h"
#include "../sdlutils/SDLUtils.h"

class Follow : public Component {
public:
	Follow(Transform* tr, Transform* cazaTr, Entity* caza) :
		tr_(tr), cazaTr_(cazaTr), caza_(caza){
	}

	virtual ~Follow() {
	}


	void update() {
		auto& p = tr_->getPos();
		auto& v = tr_->getVel();
		auto& q = cazaTr_->getPos();

		v.set(v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f));
	}

private:
	Transform* tr_;
	Transform* cazaTr_;
	Entity* caza_;
};

