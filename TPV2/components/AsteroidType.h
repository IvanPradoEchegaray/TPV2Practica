#pragma once

#include "../ecs/Component.h"

class AsteroidType : public Component {
public:
	AsteroidType(char type) : type_(type) {}
	virtual ~AsteroidType() {}
	char type() { return type_; };
private:
	char type_;
};