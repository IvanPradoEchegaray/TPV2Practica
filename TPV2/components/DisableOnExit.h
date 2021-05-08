
#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DisableOnExit : public Component {
public:
	DisableOnExit() :
		tr_(nullptr) {
	}
	virtual ~DisableOnExit() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() < 0 || pos.getX() + w > sdlutils().width() || pos.getY() < 0 || pos.getY() + h > sdlutils().height()) {
			entity_->setActive(false);
		}

	}

private:
	Transform* tr_;
};

