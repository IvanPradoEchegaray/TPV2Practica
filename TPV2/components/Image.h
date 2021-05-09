// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"

#include "Transform.h"

class Image: public Component {
public:
	Image(Texture *tex, Transform* tr) :
			tr_(tr), //
			tex_(tex) //
	{
	}
	virtual ~Image() {
	}

	void render() {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(dest, tr_->getRot());
	}

private:
	Transform *tr_;
	Texture *tex_;
};

