#include "Enemy.h"
#include "PlayState.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams) 
{
	scrolling = RESET; //스크롤 초기화
}

void Enemy::update() {
	
	m_velocity.setX(-speed); //적의 이동속도
	if (m_position.getX() <= STANDARD) //적이 왼쪽 창 밖으로 나갈 시
	{
		scrolling += speed;
	}
	if (scrolling > m_width) // 적의 넓이 값보다 왼쪽 창 밖으로 더 나갈시
	{
		PlayState::Instance()->deleteEnemy(FIRST); //먼저 생성 된 적 삭제
		return;
	}
	m_currentFrame = int(((SDL_GetTicks() / 100) % ENEMY_FRAME));
	SDLGameObject::update();
}