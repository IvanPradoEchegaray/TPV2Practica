#pragma once

#include "../ecs/Component.h"
#include "Transform.h"
#include "../sdlutils/Texture.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

class FramedImage : public Component {
public:
	FramedImage(Transform* tr, Texture* text, int filas, int columnas, float tiempoAnim, int empty) : text_(text), tr_(tr), time_(0), size_(columnas, filas)
	{
		frame = Vector2D(0, 0);
		auto w = text_->width() / columnas,
			h = text_->height() / filas;

		src = build_sdlrect(frame, w, h);
		tAnim_ = tiempoAnim;
		emptyFrames_ = empty;
		frameSize_ = Vector2D(w, h);
	};

	virtual ~FramedImage() {};

	void render() {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		text_->render(src, dest);
		if (sdlutils().currRealTime() > time_ + tAnim_) {
			time_ = sdlutils().currRealTime();
			src = nextSrcRect();
		}
	}

	SDL_Rect getFrameSize() { return src; }

private:
	SDL_Rect nextSrcRect() {
		if (frame.getX() < size_.getX() - 1) frame.setX(frame.getX() + 1);
		else {
			frame.setX(0);
			if (frame.getY() < size_.getY() - 1) frame.setY(frame.getY() + 1);
			else {
				frame.set(0, 0);
			}
		}
		if (frame.getY() == size_.getY() - 1 && frame.getX() > size_.getX() - emptyFrames_ - 1)frame.set(Vector2D(0, 0)); // ultimo sprite
		Vector2D a(frame.getX() * frameSize_.getX(), frame.getY() * frameSize_.getY());
		return build_sdlrect(a, frameSize_.getX(), frameSize_.getY());
	}

	Transform* tr_;
	Texture* text_;
	Uint32 time_;
	Vector2D frame;		// coordenadas del frame actual
	Vector2D frameSize_;
	Vector2D size_;		// tama�o del spritesheet en filas y columnas
	SDL_Rect src;
	float tAnim_;
	int emptyFrames_;
};