// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Bounce.h"
#include "../components/FighterCtrl.h"
#include "../components/Rectangle.h"
#include "../components/Rotate.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Health.h"
#include "../components/Gun.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/DeAcceleration.h"
#include "../components/Generations.h"
#include "../components/AsteroidsManager.h"
#include "../components/State.h"
#include "../components/GameCtrl.h"
#include "../components/CollisionManager.h"

#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Asteroids", 800, 600,
			"resources/config/asteroids.resources.json");
	//Systems
	gameCtrlSystem_ = mngr_.get()->addSystem<GameCtrlSystem>();
	gameCtrlSystem_->setMngr(mngr_.get());
	gameCtrlSystem_->init(); 

	fighterSystem_ = mngr_.get()->addSystem<FighterSystem>();
	fighterSystem_->setMngr(mngr_.get());
	fighterSystem_->init();

	fighterGunSystem_ = mngr_.get()->addSystem<FighterGunSystem>();
	fighterGunSystem_->setMngr(mngr_.get());
	fighterGunSystem_->init();

	asteroidsSystem_ = mngr_.get()->addSystem<AsteroidsSystem>();
	asteroidsSystem_->setMngr(mngr_.get());
	asteroidsSystem_->init();

	collisionSystem_ = mngr_.get()->addSystem<CollisionSystem>();
	collisionSystem_->setMngr(mngr_.get());
	collisionSystem_->init();

	bulletsSystem_ = mngr_.get()->addSystem<BulletsSystem>();
	bulletsSystem_->setMngr(mngr_.get());
	bulletsSystem_->init();

	renderSystem_ = mngr_.get()->addSystem<RenderSystem>();
	renderSystem_->setMngr(mngr_.get());
	renderSystem_->init();
	////Player Entidad
	//auto *player = mngr_->addEntity();
	//player->addComponent<Transform>(
	//		Vector2D(sdlutils().width() / 2.0f - 20, sdlutils().height() / 2.0f - 20),
	//		Vector2D(0.0f,0.0f), 20.0f, 20.0f, 0.0f);
	//player->addComponent<Image>(&sdlutils().images().at("fighter"));
	//player->addComponent<DeAcceleration>();
	//player->addComponent<Health>(3,
	//	Vector2D(sdlutils().width() * 0.02f, sdlutils().height() * 0.02f), 40.0f, 40.0f, 
	//	&sdlutils().images().at("heart"));
	//player->addComponent<FighterCtrl>();
	//player->addComponent<Gun>();
	//player->addComponent<ShowAtOppositeSide>();
	//gameManager Entidad
	//auto* gameManager = mngr_->addEntity();
	//gameManager->addComponent<State>();
	//gameManager->addComponent<GameCtrl>(player);
	//gameManager->addComponent<AsteroidsManager>(player);
	//gameManager->addComponent<CollisionManager>(player);

}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		gameCtrlSystem_->update();
		fighterSystem_->update();
		fighterGunSystem_->update();
		bulletsSystem_->update();
		asteroidsSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}
