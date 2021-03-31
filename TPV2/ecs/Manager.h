// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <initializer_list>
#include <vector>
#include <list>

#include "ecs.h"
#include "Entity.h"

class Manager {
public:

	Manager();
	virtual ~Manager();

	// entities
	Entity* addEntity() {
		Entity *e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			entities_.emplace_back(e);
		}
		return e;
	}

	// handlers
	template<typename T>
	inline void setHandler(Entity *e) {
		hdlrs_[ecs::hdlrIdx<T>] = e;
	}

	template<typename T>
	inline Entity* getHandler() {
		return hdlrs_[ecs::hdlrIdx<T>];
	}

	inline const std::vector<Entity*>& getEnteties() {
		return entities_;
	}

	void update();
	void render();
	void refresh();
	//Balas
	Entity* addBullet() {
		Entity* e = new Entity(this);
		if (e != nullptr) {
			e->resetGroups();
			bullet_grp.emplace_back(e);
			entities_.emplace_back(e);
		}
		return e;
	}

	inline const std::vector<Entity*>& getBullets() {
		return bullet_grp;
	}

private:

	std::vector<Entity*> entities_;
	std::vector<Entity*> bullet_grp;
	std::array<Entity*, ecs::maxHdlr> hdlrs_;

};

