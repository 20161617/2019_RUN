#include "Player.h"
#include "PlayState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "GameOverState.h"


Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams) {
	m_currentRow = RUN_ROW; 
	m_numFrames = RUN_AND_DIE_FRAME; //달리는 프레임 총 8개
	jumpCount = RESET;
	m_velocity.setX(STANDARD); //Vector값 초기화
	m_velocity.setY(STANDARD);
	m_acceleration.setY(STANDARD);
	isJump = false; //점프상태 아님
	isGround = true; //지면과 붙어있는 상태
}

void Player::update() 
{	
	m_acceleration.setY(0.25); //항상 중력값 적용
	handleInput();
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));
	SDLGameObject::update();
}

void Player::handleInput() {
	if (TheInputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_UP) && jumpCount < JUMP_LIMIT)
	{ 
		//윗 방향키를 누르고 점프제한횟수보다 점프를 하지않았다면 실행
		jump();
	}
	if (TheInputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_SPACE)) 
	{
		//스페이스 키를 눌렀을 경우 총알 생성 함수 실행 플레이어 POS값 이용
		PlayState::Instance()->createBullet(m_position.getX(), m_position.getY());
	}
}

void Player::jump()
{
	//점프 함수 실행 시
	isGround = false; //지면 상태 변경
	isJump = true; //점프 하고 있는 상태로 변경
	jumpCount++; //점프 카운트 증가
	m_velocity.setY(PLAYER_JUMP_POWER); //위로 점프힘 작용
	TheSoundManager::Instance()->playChunk(SOUND_3RD_CHANNEL, "Jump", SOUND_PLAY_ONCE); //효과음 플레이
}

void Player::setCollisionPos(SDLGameObject* p1)
{

	//플레이어가 발판 아래 부딪힐 때
	if (CheckPlayerCollision(p1, UPSIDE) == true)// 플레이어 왼쪽좌표값이 발판의 오른쪽 좌표값보다 왼쪽에 있을때
	{
	m_velocity.setY(STANDARD);
	m_position.setY(collisionDown + 1); //계속 충돌판정을 유지할 필요가 없기 때문에 장애물 보다 아래로 옮김
	}
	//플래이어가 발판을 밟고 있을 때
	else if (CheckPlayerCollision(p1, DOWNSIDE) == true) //플레이어의 아래 좌표가 발판의 아래좌표보다 위에 있을 때
	{
    m_numFrames = RUN_AND_DIE_FRAME;
	m_position.setY(collisionUp - m_height + 1); //계속 충돌판정을 유지하기 위하여
	isGround = true;
	isJump = false;
	jumpCount = RESET;
	}
	//가시에 닿았을 때
	else if (CheckPlayerCollision(p1, RIGHTSIDE) == true) //플레이어의 아래값이 장애물의 윗좌표값보다 아래에 있을 때
	{
		TheGame::Instance()->getStateMachine()->changeState(GameOverState::Instance()); //게임오버 상태 전환
	}
	
	//발판 위에 있을 시 중력종료
	if (isGround == true) {
		m_velocity.setY(STANDARD);
		m_acceleration.setY(STANDARD);
	}
}

bool Player::CheckPlayerCollision(SDLGameObject* p1, int side)
{

	collisionLeft = p1->getPosition().getX(); //충돌 대상 왼쪽좌표
	collisionRight = p1->getPosition().getX() + p1->getWidth(); //충돌 대상 오른쪽좌표
	collisionUp = p1->getPosition().getY();  //충돌 대상 윗쪽좌표
	collisionDown = p1->getPosition().getY() + p1->getHeight(); //충돌 대상 아래쪽좌표

	switch (side)
	{
	case UPSIDE:
	{
		if (m_position.getY() < collisionDown && // 플레이어의 윗값이 발판의 아래좌표보다 위에 있을 때
			m_position.getY() > collisionUp&& //플레이어의 윗값이 발판의 윗좌표보다 아래 있을 때
			m_position.getX() >= collisionLeft + (p1->getWidth() / 10) && //플레이어 왼쪽좌표값이 발판의 왼쪽 좌표 값보다 오른쪽에 있을때
			m_position.getX() <= collisionRight)
		{
			return true;
		}
		break;
	}
	case DOWNSIDE:
	{
		if ((m_position.getX() >= collisionLeft + ((p1->getWidth() / 10) - 1) &&  //플레이어 왼쪽좌표값이 발판의 왼쪽 좌표 값보다 오른쪽에 있고
			m_position.getX() <= collisionRight) && // 플레이어 왼쪽좌표값이 발판의 오른쪽 좌표값보다 왼쪽에 있을때
			m_position.getY() + m_height > collisionUp&& //플레이어의 아래 좌표가 발판의 윗좌표보다 아래있을 때
			m_position.getY() + m_height < collisionDown)
		{
			return true;
		}
		break;
	}
	case RIGHTSIDE:
	{
		if (m_position.getX() + m_width > collisionLeft&& //플레이어의 오른쪽 값에서 빈공간을 뺀값이 발판의 왼쪽보다 오른쪽에 있을 때
			m_position.getX() + m_width < collisionRight && //플레이어의 오른쪽 값에서 빈공간을 뺀값이 발판의 오른쪽 좌표보다 왼쪽에 있을 때
			m_position.getX() < collisionLeft && //플레이어의 왼쪽값이 발판의 왼쪽 좌표보다 왼쪽에 있을 때
			m_position.getY() + m_height > collisionUp)
		{
			return true;
		}
		break;
	}
	default:
		break;
	}
	return false;
}

