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
	FighterCtrl() :
			tr_(nullptr), thrust_(0.1), speedLimit_(3.0f){
	}
	virtual ~FighterCtrl() {
	}


	inline void setSpeed(float thrust) {
		thrust_ = thrust_;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto &vel = tr_->getVel();
			if (ih().isKeyDown(SDLK_UP)) {
				vel = speedUp(vel,tr_->getRot());
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

private:
	Transform *tr_;
	float thrust_;
	float speedLimit_;
}
;

