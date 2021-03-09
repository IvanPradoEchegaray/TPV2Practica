#pragma once
#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"


class Caza :public Entity
{
public:
	explicit Caza(Manager * mngr_, Vector2D pos, Vector2D vel, float wSize_, float hSize_, std::string tex_);
	
protected:
	double rot;
};
