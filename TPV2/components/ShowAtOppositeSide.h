// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class ShowAtOppositeSide : public Component {
public:
	ShowAtOppositeSide() :
		tr_(nullptr) {
	}
	virtual ~ShowAtOppositeSide() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() < 0) {
			pos.setX(sdlutils().width() - w);
		}
		else if (pos.getX() + w > sdlutils().width()) {
			pos.setX(0.0);
		}

		if (pos.getY() < 0) {
			pos.setY(sdlutils().height() - h);
		}
		else if (pos.getY() + h > sdlutils().height()) {
			pos.setY(0.0);

		}


	}

private:
	Transform* tr_;
};

