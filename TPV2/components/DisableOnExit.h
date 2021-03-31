
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

	void update() override {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() < 0) {
			this->getEntity()->setActive(false);
		}
		else if (pos.getX() + w > sdlutils().width()) {
			this->getEntity()->setActive(false);
		}

		if (pos.getY() < 0) {
			this->getEntity()->setActive(false);
		}
		else if (pos.getY() + h > sdlutils().height()) {
			this->getEntity()->setActive(false);
		}


	}

private:
	Transform* tr_;
};

