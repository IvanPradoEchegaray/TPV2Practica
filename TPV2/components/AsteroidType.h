#pragma once

#include "../ecs/Component.h"

class AsteroidType : public Component {
public:
	AsteroidType(char t) : type_(t) {}
	virtual ~AsteroidType() {}
	char getType() { return type_; };
	void setType(char t) { type_ = t; };
private:
	char type_;
};