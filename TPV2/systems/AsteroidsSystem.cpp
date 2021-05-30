#include "AsteroidsSystem.h"

void AsteroidsSystem::init() {
	startTime_ = sdlutils().currRealTime();
}

void AsteroidsSystem::addAsteroids(int n)
{
	for (int i = 0; i < n; i++)
	{
		auto* asteroide = manager_->addEntity();
		numOfAsteroids_++;

		//Componentes--------------------------------------------------------------------------------------------
		manager_->addComponent<Transform>(asteroide);
		manager_->addComponent<Generations>(asteroide, manager_->getComponent<Transform>(asteroide));
			//TIPO B
		//---------------------------------------------------------------------------------------------------------

		// Calculo la posicion inicial del asteroide de forma aleatoria
		int colu = sdlutils().rand().nextInt(0, 11);
		int fil;
		if (0 < colu && colu < 10) {
			fil = sdlutils().rand().nextInt(0, 2);
			if (fil == 1) fil = 10;
		}
		else {
			fil = sdlutils().rand().nextInt(0, 11);
		}

		if (sdlutils().rand().nextInt(0, 10) < 3) {
			//Debug Log
			std::cout << "--" << colu << ", " << fil << " TIPO B --\n";
			manager_->addComponent<Follow>(asteroide, manager_->getComponent<Transform>(asteroide), manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>()));
			manager_->addComponent<FramedImage>(asteroide, manager_->getComponent<Transform>(asteroide), &sdlutils().images().at("asteroid_gold"), 5, 6, 2, 0);
			manager_->addComponent<AsteroidType>(asteroide, 'b');
		}
			//TIPO A
		else {
			//Debug Log
			std::cout << "--" << colu << ", " << fil << " TIPO A --\n";
			manager_->addComponent<FramedImage>(asteroide, manager_->getComponent<Transform>(asteroide), &sdlutils().images().at("asteroid"), 5, 6, 2, 0);
			manager_->addComponent<AsteroidType>(asteroide, 'a');
		}
		Vector2D* p = new Vector2D(sdlutils().width() * colu / 10, sdlutils().height() * fil / 10);
		Vector2D* c = new Vector2D((sdlutils().width() / 2) + sdlutils().rand().nextInt(-100, 101),
			(sdlutils().height() / 2) + sdlutils().rand().nextInt(-100, 101));
		Vector2D* veln = new Vector2D(c->getX() - p->getX(), c->getY() - p->getY());

		manager_->getComponent<Transform>(asteroide)->getPos().set(p);
		manager_->getComponent<Transform>(asteroide)->getVel().set(veln->normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0));

		manager_->setGroup<Asteroid_grp>(asteroide, true);
	}
}

void AsteroidsSystem::onCollisionWithBullet(Entity* a, Entity* b)
{
	//DIVIDE ON COLLISION-------------------------------------------------------------------------------
	if (manager_->getComponent<Generations>(a)->getGenerations() > 0) {
		for (int i = 0; i < 2; i++)
		{
			auto* asteroide = manager_->addEntity();
			numOfAsteroids_++;

			//Componentes--------------------------------------------------------------------------------------------
			manager_->addComponent<Transform>(asteroide);
			manager_->addComponent<Generations>
				(asteroide, manager_->getComponent<Transform>(asteroide), manager_->getComponent<Generations>(a)->getGenerations() - 1);
			//TIPO B
			if (sdlutils().rand().nextInt(0, 10) < 3) {
				//Debug Log
				//std::cout << "--" << colu << ", " << fil << " TIPO B --\n";
				manager_->addComponent<Follow>(asteroide, manager_->getComponent<Transform>(asteroide), manager_->getComponent<Transform>(manager_->getHandler<Player1Handler>()));
				manager_->addComponent<FramedImage>(asteroide, manager_->getComponent<Transform>(asteroide), &sdlutils().images().at("asteroid_gold"), 5, 6, 2, 0);
				manager_->addComponent<AsteroidType>(asteroide, 'b');
			}
			//TIPO A
			else {
				//Debug Log
				//std::cout << "--" << colu << ", " << fil << " TIPO A --\n";
				manager_->addComponent<FramedImage>(asteroide, manager_->getComponent<Transform>(asteroide), &sdlutils().images().at("asteroid"), 5, 6, 2, 0);
				manager_->addComponent<AsteroidType>(asteroide, 'a');
			}
			//---------------------------------------------------------------------------------------------------------

			Vector2D pos = manager_->getComponent<Transform>(a)->getPos();
			Vector2D vel = manager_->getComponent<Transform>(a)->getVel();
			float w = manager_->getComponent<Transform>(a)->getW();

			int r = sdlutils().rand().nextInt(0, 360);
			manager_->getComponent<Transform>(asteroide)->getPos().set(pos + vel.rotate(r) * 2 * w);
			manager_->getComponent<Transform>(asteroide)->getVel().set(vel.rotate(r) * 1.1f);

			manager_->setGroup<Asteroid_grp>(asteroide, true);
		}
	}
	//---------------------------------------------------------------------------------------------

	manager_->setActive(a, false);
	//manager_->send(BulletAsteroidCollision(b, a));
}

void AsteroidsSystem::update() {
	if (manager_->getSystem<GameCtrlSystem>()->getGameState() == RUNNING) {
		Uint32 currentTime = sdlutils().currRealTime() - startTime_;
		if (currentTime >= 5000) {
			startTime_ = sdlutils().currRealTime();
			addAsteroids(1);
		}
	}
	for (Entity* e : manager_->getEnteties()) {
		if (manager_->hasGroup<Asteroid_grp>(e)) {
			if(manager_->getComponent<Follow>(e))
			manager_->getComponent<Follow>(e)->update();
			manager_->getComponent<Transform>(e)->update();
		}
	}
}

const int& AsteroidsSystem::getNumAsteroids()
{
	return numOfAsteroids_;
}
