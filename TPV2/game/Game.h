// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_stdinc.h>
#include <memory>


// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;
class System;

class Game {
public:
	Game();
	virtual ~Game();
	void init(const char* host, Uint16 port);
	void start();
private:
	std::unique_ptr<Manager> mngr_;
	System* networkSys_;
	System* gameCtrlSystem_;
	System* fighterSystem_;
	System* fighterGunSystem_;
	System* bulletsSystem_;
	System* asteroidsSystem_;
	System* collisionSystem_;
	System* renderSystem_;
};

