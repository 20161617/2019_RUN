#include "Game.h"
#include "AnimateGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams* pParams, int animSpeed)
	:SDLGameObject(pParams), m_animSpeed(animSpeed)
{
	m_numFrames = RUN_AND_DIE_FRAME;
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}