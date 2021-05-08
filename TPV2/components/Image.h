// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture *tex) :
			tr_(nullptr), //
			tex_(tex) //
	{
	}
	virtual ~Image() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void render() override {
		Vector2D pos = Vector2D(tr_->getPos().getX() - (tr_->getW() / 2.0), tr_->getPos().getY() - (tr_->getH() / 2.0));
		SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
};

