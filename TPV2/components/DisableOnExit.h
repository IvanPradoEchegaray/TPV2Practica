
#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"

class DisableOnExit : public Component {
public:
	DisableOnExit(Transform* tr, Manager* mngr,Entity* e) :
		tr_(tr), mngr_(mngr), entity_(e) {
	}
	virtual ~DisableOnExit() {
	}

	void update() {
		auto& pos = tr_->getPos();
		auto w = tr_->getW();
		auto h = tr_->getH();

		if (pos.getX() < 0 || pos.getX() + w > sdlutils().width() || pos.getY() < 0 || pos.getY() + h > sdlutils().height()) {
			mngr_->setActive(entity_, false);
		}

	}

private:
	Transform* tr_;
	Entity* entity_;
	Manager* mngr_;
};

