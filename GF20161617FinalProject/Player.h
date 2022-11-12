#pragma once
#include "SDLGameObject.h"
#include "SoundManager.h"

enum SIDE
{
	DEFAULT = 0,
	UPSIDE = 1,
	DOWNSIDE = 2,
	RIGHTSIDE = 3
};

class Player :public SDLGameObject {
public:
	Player(const LoaderParams* pParams);
	virtual void update();
	void handleInput();
	void setCollisionPos(SDLGameObject* p1); //checkCollision함수가 실행될시 실행됨
	void jump(); //플레이어 점프 함수
	void setIsGroundFalse()	{isGround = false;	m_numFrames = STOP_FRAME;} //공중상태로 바꿈 프레임을 고정시킴

public:
	bool CheckPlayerCollision(SDLGameObject* p1, int side);

private:
	bool isGround; //지면에 있는 상태
	bool isJump; //점프 상태
	int jumpCount; //점프 횟수
	float collisionLeft; //충돌 대상 개체 왼쪽 좌표
	float collisionRight; //충돌 대상 개체 오른쪽 좌표
	float collisionUp; //충돌 대상 개체 윗쪽 좌표
	float collisionDown; //충돌 대상 개체 아래쪽 좌표

private:

};