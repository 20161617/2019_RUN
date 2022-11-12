#include "GameOverState.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "AnimateGraphic.h"
#include "BackGround.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";
GameOverState* GameOverState::s_pInstance = NULL;

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void GameOverState::update()
{
	GameState::update();
}

void GameOverState::render()
{
	GameState::render();
	//텍스트와 점수 렌더링
	TheTextManager::Instance()->drawText("Text", (TheGame::Instance()->getWindowSize("width") / 2) - TEXT_POSX,
		(TheGame::Instance()->getWindowSize("height") / 2), TEXT_WIDTH, TEXT_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	TheTextManager::Instance()->drawText("Score", ((TheGame::Instance()->getWindowSize("width") / 2) + SCORE_POSX),
		(TheGame::Instance()->getWindowSize("height") / 2), (SCORE_WIDTH * PlayState::Instance()->getDigit()), SCORE_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
}

bool GameOverState::onEnter()
{
	//플레이어 죽는 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/PlayerCharacterDie.png", "PlayerDie",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//메뉴 버튼 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/mainmenuButton.png", "Mainbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//재시작 버튼 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/restartButton.png", "Restartbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//게임오버 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/gameover.png", "Gameover",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* playerDie = new AnimatedGraphic(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) -
		(DIE_PLAYER_WIDTH / 2), (TheGame::Instance()->getWindowSize("height") / 2) - DIE_PLAYER_POSY,
		DIE_PLAYER_WIDTH, DIE_PLAYER_HEIGHT, "PlayerDie"), PLAYER_DIE_ANIMATION_SPEED);
	GameObject* restartButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + UPSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "Restartbutton"), s_restartPlay);
	GameObject* mainButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + DOWNSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "Mainbutton"), s_gameOverToMain);
	GameObject* gameover = new BackGround(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (GAMEOVER_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) - GAMEOVER_POSY, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, "Gameover"));


	m_gameObjects.push_back(playerDie);
	m_gameObjects.push_back(restartButton);
	m_gameObjects.push_back(mainButton);
	m_gameObjects.push_back(gameover);

	resetText(); //점수 텍스트 리셋

	//텍스트 로드
	TheTextManager::Instance()->loadText("Text", "Score : ", { WHITE, WHITE, WHITE }, TheGame::Instance()->getRenderer());
	TheTextManager::Instance()->loadText("Score", readScore.str(), { WHITE, WHITE, WHITE }, TheGame::Instance()->getRenderer());
	std::cout << "entering GameOverState\n";

	SDLGameObject::speedReset(); //스피드 리셋
	return true;
}

bool GameOverState::onExit()
{
	TheTextureManager::Instance()->clearFromTextureMap("PlayerDie");
	TheTextureManager::Instance()->clearFromTextureMap("Mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("Restartbutton");
	TheTextureManager::Instance()->clearFromTextureMap("Gameover");
	TheTextManager::Instance()->clearFromTextMap("Text");
	TheTextManager::Instance()->clearFromTextMap("Score");
	std::cout << "exiting GameOverState\n";
	return GameState::onExit();
}

void GameOverState::resetText() //텍스트에 저장 되어 있는 점수 초기화
{
	readScore.str(""); //초기화
	readScore.clear(); //초기화
	readScore << PlayState::Instance()->getScore(); //값 입력
}