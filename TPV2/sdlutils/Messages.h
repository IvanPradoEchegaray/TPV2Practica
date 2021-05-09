#pragma once
#include <SDL_stdinc.h>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"

enum MsgId :Uint8 {
	Fighter_Asteroid_Collision, Bullet_Asteroid_Collision
};

struct Message {
	Message(MsgId id) :id_(id) {}
	virtual Message* clone() const {
		return new Message(*this);
	}
	MsgId id_;
};

struct FighterAsteroidCollision : Message
{
	FighterAsteroidCollision(Entity* p, Entity* a) : Message(Fighter_Asteroid_Collision), player_(p), asteroid_(a) {}
	Entity* player_;
	Entity* asteroid_;
};
struct BulletAsteroidCollision : Message
{
	BulletAsteroidCollision(Entity* b, Entity* a) : Message(Bullet_Asteroid_Collision), bullet_(b), asteroid_(a) {}
	Entity* bullet_;
	Entity* asteroid_;
};

