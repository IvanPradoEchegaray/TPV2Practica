#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Rotate.h"
#include "../sdlutils/SDLUtils.h"

class Follow : public Component {
public:
	Follow(Entity* caza) :
		tr_(nullptr), cazaTr_(nullptr), caza_(caza){
	}

	virtual ~Follow() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

		cazaTr_ = caza_->getComponent<Transform>();
		assert(cazaTr_ != nullptr);
	}

	void update() override {
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

