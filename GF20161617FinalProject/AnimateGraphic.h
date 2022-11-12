#pragma once
#include "SDLGameObject.h"


class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed);
	virtual void update();

private:
	int m_animSpeed;
};
