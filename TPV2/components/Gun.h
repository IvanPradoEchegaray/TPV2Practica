#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "Image.h"
#include "DisableOnExit.h"
#include "../ecs/Manager.h"

class Gun : public Component {
public:
	Gun() :
		tr_(nullptr) {
	}
	virtual ~Gun() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		startTime_ = sdlutils().currRealTime();
	}

	void update() override {
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_s) && entity_->getComponent<FighterCtrl>()->inputIsEnabled()) {
				createBullet();
			}
		}
	}

	void createBullet() {
		Uint32 currentTime = sdlutils().currRealTime() - startTime_;
		if (currentTime >= 250) {
			//Bala
			Vector2D bPos = tr_->getPos() + Vector2D(tr_->getW() / 2.0f, tr_->getH() / 2.0f) - Vector2D(0.0f, tr_->getH() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot()) - Vector2D(2.0f, 10.0f);
			Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);
			auto* bala = entity_->getMngr()->addEntity();
			bala->addComponent<Transform>(bPos, bVel, 5.0f, 20.f, tr_->getRot());
			bala->addComponent<Image>(&sdlutils().images().at("fire"));
			bala->addComponent<DisableOnExit>();
			bala->setGroup<Bullet_grp>(true);
			//Sonido a reproducir
			sdlutils().soundEffects().at("fire").play();
			startTime_ = sdlutils().currRealTime();
		}
	}


private:
	Transform* tr_;
	Uint32 startTime_;
}
;
