#pragma once
#include <iostream>
#include <vector>
#include "GameEnum.h"
#include "SoundManager.h"
#include "TextManager.h"
#include "Game.h"

using namespace std;

class GameObject;

class GameState {
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter() = 0;
	virtual bool onExit();
	virtual std::string getStateID() const = 0;
protected:

	//기본 게임 오브젝트 벡터
	std::vector<GameObject*>m_gameObjects;
	//탄환전용 벡터 생성
	std::vector<GameObject*>m_gameBullets;
	//플렛폼 전용 벡터
	std::vector<GameObject*>m_gamePlatforms;
	//적 전용 벡터
	std::vector<GameObject*>m_gameEnemys;
};