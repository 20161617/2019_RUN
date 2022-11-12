#pragma once
#include "GameState.h"
#include <vector>
class GameStateMachine {
public:
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();

private:
	GameState* m_currentState; //현재 상태
	GameState* m_prevState; //이전 상태
};