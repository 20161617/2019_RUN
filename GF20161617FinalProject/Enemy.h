#pragma once
#include "SDLGameObject.h"

class Enemy :public SDLGameObject {
public:
	Enemy(const LoaderParams* pParams);
	virtual void update();
};