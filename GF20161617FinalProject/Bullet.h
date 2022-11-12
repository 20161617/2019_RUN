#pragma once
#include "SDLGameObject.h"

class Bullet :public SDLGameObject {
public:
	Bullet(const LoaderParams* pParams);
	virtual void update();
};
