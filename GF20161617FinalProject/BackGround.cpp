#include "BackGround.h"

BackGround::BackGround(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
	scrolling = RESET;
	m_velocity.setX(STANDARD);
	m_velocity.setY(STANDARD);
}

void BackGround::update() {

	//배경화면과 플랫폼에만 적용, 게임제목 일시정지 혹은 게임오버상태에는 미적용
	if (m_textureID == "Background") 
	{
		m_velocity.setX(-speed);
		if (scrolling < m_width) // 이동거리가 배경화면 보다 작으면
		{
			scrolling += speed;
		}
		if (scrolling >= m_width) //이동거리가 배경화면보다 크면 0으로 초기화
		{
			scrolling = RESET;
			m_position.setX(STANDARD);
		}
	}
	else if (m_textureID == "Platform")
	{
		m_velocity.setX(-speed);
		if (m_position.getX() <= STANDARD) //플랫폼의 X좌표값이 창의 왼쪽 값보다 작으면
		{
			scrolling += speed;
		}
	}
	m_currentFrame = int(((SDL_GetTicks() / 100) % BACKGROUND_FRAME));
	SDLGameObject::update();
}


