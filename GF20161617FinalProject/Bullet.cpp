#include "bullet.h"
#include "PlayState.h"
#include "Game.h"

Bullet::Bullet(const LoaderParams* pParams) :
	SDLGameObject(pParams) {}


void Bullet::update() {
	m_velocity.setX(BULLET_SPEED); //총알의 속도 12
	if (m_position.getX() >= TheGame::Instance()->getWindowSize("width")) //총알이 왼쪽 창 밖으로 나가면
	{
		PlayState::Instance()->deleteBullet(FIRST); //맨 처음에 쏜 총알 삭제
	}
	SDLGameObject::update();
}

