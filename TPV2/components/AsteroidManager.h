#pragma once

#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Generations.h"
#include "Transform.h"
#include "../game/Game.h"

class AsteroidManager : public Component {
public:
	AsteroidManager() {}

	virtual ~AsteroidManager() {}

	void init() override {
		
	}

	void generaAsteroide() {
		//auto* asteroid = mngr_->addEntity();
		//
		//int colu = sdlutils().rand().nextInt(0, 11);
		//int fil;
		//if (0 < colu && colu < 10) {
		//	fil = sdlutils().rand().nextInt(0, 2);
		//	if (fil == 1) fil = 10;
		//}
		//else {
		//	fil = sdlutils().rand().nextInt(0, 11);
		//}
		//
		//Vector2D* p = new Vector2D(sdlutils().width() * colu / 10, sdlutils().height() * fil / 10);
		//std::cout << colu << ", " << fil;
		//Vector2D* c = new Vector2D((sdlutils().width() / 2) + sdlutils().rand().nextInt(-100, 101),
		//	(sdlutils().height() / 2) + sdlutils().rand().nextInt(-100, 101));
		//
		//Vector2D* veln = new Vector2D(c->getX() - p->getX(), c->getY() - p->getY());
		//
		//asteroid->addComponent<Transform>(p, Vector2D(1.0f, 0.0f), 40.0f, 40.0f, 0.0f);
		//auto& v = asteroid->getComponent<Transform>()->getVel();
		//v.set(veln.normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0));
		//asteroid->addComponent<Generations>();
		//asteroid->addComponent<Follow>(ball);
		//asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"), 5, 6, 2, 0);
	}
};
