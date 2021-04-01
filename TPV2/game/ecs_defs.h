// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class FighterCtrl;
class Bounce;
class Image;
class Rotate;
class ShowAtOppositeSide;
class DisableOnExit;
class DeAcceleration;
class Health;
class Follow;
class FramedImage;
class Generations;
class AsteroidsManager;

#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	FighterCtrl,\
	Bounce,\
	Image,\
	Rotate,\
	ShowAtOppositeSide,\
	DisableOnExit,\
	DeAcceleration,\
	Health,\
	Follow,\
	FramedImage,\
	Generations,\
	AsteroidsManager

// groups

struct Bullet_grp;
#define _GRPS_LIST_ Bullet_grp

struct Asteroid_grp;
#define _GRPS_LIST_  Asteroid_grp

// handlers
struct Hdlr_1;
#define _HDLRS_LIST_ Hdlr_1
