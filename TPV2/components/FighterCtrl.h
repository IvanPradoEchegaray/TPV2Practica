// This file is part of the course TPV2@UCM - Samir Genaim

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
		startTime_ = sdlutils().currRealTime();
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
			} if (ih().isKeyDown(SDLK_SPACE)) {
				createBullet(vel);
			}
		}
	}

	Vector2D speedUp(Vector2D& vel, float r) {
		Vector2D newVel = Vector2D(vel + Vector2D(0, -1).rotate(r) * thrust_);
		if (newVel.getX()>= speedLimit_ || newVel.getY() >= speedLimit_)	//Velocidad Limite
			newVel.normalize()* speedLimit_;
		return newVel;
	}

	void createBullet(Vector2D& vel) {
		Uint32 currentTime_ = sdlutils().currRealTime() - startTime_;
		if (currentTime_ >= 250) {
			//Bala
			auto* bala = this->getEntity()->getMngr()->addBullet();
			bala->addComponent<Transform>(Vector2D(tr_->getPos().getX() + tr_->getW() / 2, tr_->getPos().getY() + tr_->getH() / 2),
				Vector2D(vel + Vector2D(0, -1).rotate(tr_->getRot()) * 4.0f), 20.0f, 20.f, tr_->getRot());
			bala->addComponent<Image>(&sdlutils().images().at("fire"));
			//bala->addComponent<DisableOnExit>();
			//Sonido a reproducir
			
			startTime_ = sdlutils().currRealTime();
		}
	}


private:
	Transform *tr_;
	float thrust_;
	float speedLimit_;
	Uint32 startTime_;
}
;

