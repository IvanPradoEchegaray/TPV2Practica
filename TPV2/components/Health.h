#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Image.h"
#include "../sdlutils/SDLUtils.h"

class Health : public Component {
public:
	Health(size_t vidas_) : vidas(vidas_) {
	}
	virtual ~Health() {
	}
	void init() override {
		hearts.reserve(vidas);
		for (int i = 0; i < vidas; i++) {
			hearts.emplace_back(new Entity(nullptr));
			hearts[i]->addComponent<Transform>(Vector2D(sdlutils().width() * 0.1f, sdlutils().height() * 0.1f),
				Vector2D(), 30.0f, 30.0f, 0.0f);
			hearts[i]->addComponent<Image>(&sdlutils().images().at("heart"));
		}
	}

	void update() override {
		if (hearts.size() != vidas) {
			hearts.resize(vidas);
		}
	}

private:
	size_t vidas;
	std::vector<Entity*> hearts;
};
