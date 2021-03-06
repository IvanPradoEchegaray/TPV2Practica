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
class Gun;
class State;
class GameCtrl;
class CollisionManager;
class AsteroidType;

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
	Gun,\
	AsteroidsManager,\
	State,\
	GameCtrl,\
	CollisionManager,\
	AsteroidType

// groups

struct Bullet_grp;
struct Asteroid_grp;

#define _GRPS_LIST_ \
	Bullet_grp,\
	Asteroid_grp

// handlers
struct Player1Handler;
struct Player2Handler;
struct GameManager;
#define _HDLRS_LIST_  \
Player1Handler, \
Player2Handler, \
GameManager

// systems
class GameCtrlSystem;
class BulletsSystem;
class FighterGunSystem;
class AsteroidsSystem;
class CollisionSystem;
class FighterSystem;
class RenderSystem;
class NetworkSystem;

#define _SYS_LIST_ \
GameCtrlSystem, \
BulletsSystem, \
FighterGunSystem, \
AsteroidsSystem, \
CollisionSystem, \
FighterSystem, \
RenderSystem,\
NetworkSystem
