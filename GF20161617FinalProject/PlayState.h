#pragma once
#include "GameState.h"
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

class SDLGameObject;



class PlayState : public GameState {
public:
	static PlayState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new PlayState();
		}
		return s_pInstance;
	}

	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_playID; }
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	void createBullet(int x, int y); //총알 생성
	void deleteBullet(int i); //총알 삭제
	void createPlatform(); //플랫폼 생성
	void deletePlatform(int i); //플랫폼 삭제
	void createEnemy(); //적 생성
	void deleteEnemy(int i); //적 삭제
	void reset() { //점수, 레벨 업 점수, 적 최대 마리 제한, 점수의 자릿수 초기화
		score = START_SCORE; devideScore = START_DEVIDE_SCORE; enemyLimit = START_ENEMY; digit = START_DIGIT;
	}
	void upScore(std::string reason); //점수증가 reason을 비교하여 몇점오를지 결정
	int getScore() { return score; } //점수 리턴, 게임오버 상태에서 사용 중
	int getDigit() { return digit; } //자릿 수 리턴, 게임오버 상태에서 사용 중
private:
	PlayState() 
	{
		//적 최대 마리, 레벨업 점수, 레벨업가능유뮤변수, 랜덤 Y값, 플랫폼 생성,삭제 변수, 랜덤함수관련 초기화
		enemyLimit = START_ENEMY; devideScore = START_DEVIDE_SCORE; 
		isLevelUp = false; randomPosY = POS_ZERO; checkNum = START_NUM;
		srand((unsigned)time(NULL));
	}
	static PlayState* s_pInstance;
	static const std::string s_playID;
	int enemyLimit; //적 최대 마리
	int randomPosY; //플랫폼 랜덤 Pos Y값
	int devideScore; //레벨 업 점수
	bool isLevelUp; //레벨업 가능 유뮤 false일 시 가능
	int checkNum; //플랫폼 생성, 삭제 관련 변수
	ostringstream readScore; //점수 텍스트용
	static int score; //점수
	static int digit; //자릿 수
};
