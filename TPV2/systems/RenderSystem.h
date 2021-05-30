#pragma once
#include "../ecs/System.h"
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/FramedImage.h"
#include "../components/Image.h"
#include "../components/Health.h"
#include "GameCtrlSystem.h"
class RenderSystem : public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();
	void init() override;
	void update() override;
private:

	void drawScore();
	void drawMsgs();
	void drawNames();

	Transform* player1Tr_;
	Transform* player2Tr_;
};

