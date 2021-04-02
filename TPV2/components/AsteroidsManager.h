#pragma once

#include "FramedImage.h"
#include "Follow.h"
#include "Generations.h"
#include "Transform.h"

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../game/Game.h"

class AsteroidsManager : public Component {
public:
	AsteroidsManager(Entity* player) : player_(player) {}

	virtual ~AsteroidsManager() {}

	void init() override {
		mngr_ = entity_->getMngr();
		startTime_ = sdlutils().currRealTime();
	}

	void update() override {
		//Debug Log
		std::cout << nAsteroides_ << "\n";

		//Genera 1 asteroide nuevo cada 5 segundos
		Uint32 currentTime = sdlutils().currRealTime() - startTime_;
		if (currentTime >= 5000) {
			startTime_ = sdlutils().currRealTime();
			generaAsteroide();
		}
	}

	int getNumAsteroides() {
		return nAsteroides_;
	}

	void OnCollision(Entity* asteroide) {
		collisionTr_ = asteroide->getComponent<Transform>();
		assert(collisionTr_ != nullptr);

		gen_ = asteroide->getComponent<Generations>()->getGenerations();

		auto& p = collisionTr_->getPos();
		auto& v = collisionTr_->getVel();

		asteroide->setActive(false);
	}

	void generaAsteroide() {
		auto* asteroid = mngr_->addEntity();
		nAsteroides_++;

		int colu = sdlutils().rand().nextInt(0, 11);
		int fil;
		if (0 < colu && colu < 10) {
			fil = sdlutils().rand().nextInt(0, 2);
			if (fil == 1) fil = 10;
		}
		else {
			fil = sdlutils().rand().nextInt(0, 11);
		}

		Vector2D* p = new Vector2D(sdlutils().width() * colu / 10, sdlutils().height() * fil / 10);
		Vector2D* c = new Vector2D((sdlutils().width() / 2) + sdlutils().rand().nextInt(-100, 101),
			(sdlutils().height() / 2) + sdlutils().rand().nextInt(-100, 101));
		Vector2D* veln = new Vector2D(c->getX() - p->getX(), c->getY() - p->getY());

		asteroid->addComponent<Transform>(p, Vector2D(1.0f, 0.0f), 40.0f, 40.0f, 0.0f);
		auto& v = asteroid->getComponent<Transform>()->getVel();
		v.set(veln->normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0));
		asteroid->addComponent<Generations>();

		//DIFERENCIACION DE TIPOS
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			//Debug Log
			std::cout << "--" << colu << ", " << fil << " TIPO B --\n";
			asteroid->addComponent<Follow>(player_);
			asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"), 5, 6, 2, 0);
		}

		else {
			//Debug Log
			std::cout << "--" << colu << ", " << fil << " TIPO B --\n";
			asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 2, 0);
		}
	}
private:
	Transform* collisionTr_;
	int gen_;
	Manager* mngr_;
	Entity* player_;
	int nAsteroides_;
	Uint32 startTime_;
};
