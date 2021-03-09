#include "Caza.h"

Caza::Caza(Manager* mngr_, Vector2D pos, Vector2D vel, float wSize_, float hSize_, std::string tex_) : Entity(mngr_)
{
	this->addComponent<Transform>(pos, vel, wSize_, hSize_);
	this->addComponent<Image>(&sdlutils().images().at(tex_));
	this->addComponent<ShowAtOppositeSide>();
	rot = 90.0;
}


