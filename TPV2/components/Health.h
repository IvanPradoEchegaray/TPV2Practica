#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

class Health : public Component {
public:
	Health(size_t vidas, Vector2D pos, float w, float h, Texture* tex) : max_vidas_(vidas), pos_(pos), width_(w), heigth_(h), tex_(tex) {
		resetLifes();
	}
	virtual ~Health() {
	}
	void render() {
		for (int i = 0; i < vidas_; i++) {
			Vector2D pos = Vector2D(pos_.getX() + width_ * i, pos_.getY());
			SDL_Rect dest = build_sdlrect(pos, width_, heigth_);
			tex_->render(dest, 0);
		}
	}

	void loseLife() { vidas_--; }
	const size_t& getLifes() { return vidas_; }
	bool isDead() {
		if (vidas_ <= 0) return true;
		else return false;
	}
	void resetLifes() { vidas_ = max_vidas_; }

private:
	Texture* tex_;
	Vector2D pos_;
	float width_, heigth_;
	size_t vidas_; 
	size_t max_vidas_;
};
