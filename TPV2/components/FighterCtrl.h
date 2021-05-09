// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../ecs/Manager.h"

class FighterCtrl: public Component {
public:
	FighterCtrl(Transform* tr) :
			tr_(tr), thrust_(0.1), speedLimit_(3.0f){
		ableInput_ = false;
	}
	virtual ~FighterCtrl() {
	}


	inline void setSpeed(float thrust) {
		thrust_ = thrust_;
	}

	void update() {
		if (ih().keyDownEvent() && ableInput_) {
			auto &vel = tr_->getVel();
			if (ih().isKeyDown(SDLK_UP)) {
				vel = speedUp(vel,tr_->getRot());
				//Sonido a reproducir
				sdlutils().soundEffects().at("thrust").play();
			} if (ih().isKeyDown(SDLK_LEFT)) {
				tr_->setRot(tr_->getRot() - 5.0f);
			} else if (ih().isKeyDown(SDLK_RIGHT)) {
				tr_->setRot(tr_->getRot() + 5.0f);
			}
		}
	}

	Vector2D speedUp(Vector2D& vel, float r) {
		Vector2D newVel = Vector2D(vel + Vector2D(0, -1).rotate(r) * thrust_);
		if (newVel.magnitude() >= speedLimit_)	//Velocidad Limite
			newVel = vel.normalize()* speedLimit_;
		return newVel;
	}

	void enableInput(bool state) { ableInput_ = state; }
	const bool& inputIsEnabled() { return ableInput_; }
private:
	Transform *tr_;
	float thrust_;
	float speedLimit_;
	bool ableInput_;
}
;

