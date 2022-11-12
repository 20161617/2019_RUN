
#include "GameState.h"
#include <iostream>

class GameObject;

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_gameOverID; }
	void resetText(); //점수 텍스트 리셋
	static GameOverState* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}

private:
	GameOverState() {}
	static void s_gameOverToMain();
	static void s_restartPlay();
	static const std::string s_gameOverID;
	static GameOverState* s_pInstance;
	ostringstream readScore; //점수 텍스트를 입력받음
};