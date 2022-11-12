#include "PauseState.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "AnimateGraphic.h"
#include "BackGround.h"

PauseState* PauseState::s_pInstance = NULL;

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::update()
{
	GameState::update();
}

void PauseState::render()
{
	GameState::render();
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(MenuState::Instance());
}

void PauseState::s_resumePlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}

bool PauseState::onEnter()
{
	//플레이어 달리는 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/PlayerCharacterRun.png", "PlayerPause",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//일시정지 해제 버튼 로드
	if (!TheTextureManager::Instance()->load("assets/resumeButton.png", "Resumebutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//메인메뉴버튼 로드
	if (!TheTextureManager::Instance()->load("assets/mainmenuButton.png", "Mainbutton",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//일시정지 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/pause.png", "Pause",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* player = new AnimatedGraphic(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) -
		(PLAYER_WIDTH / 2), (TheGame::Instance()->getWindowSize("height") / 2) - PAUSE_PLAYER_POSY,
		PLAYER_WIDTH, PLAYER_HEIGHT, "PlayerPause"), PLAYER_RUN_ANIMATION_SPEED);
	GameObject* resumeButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + UPSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "Resumebutton"),
		s_resumePlay);
	GameObject* mainButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + DOWNSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "Mainbutton"),
		s_pauseToMain);
	GameObject* pause = new BackGround(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (PAUSE_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) - PAUSE_POSY, PAUSE_WIDTH, PAUSE_HEIGHT, "Pause"));

	m_gameObjects.push_back(player);
	m_gameObjects.push_back(resumeButton);
	m_gameObjects.push_back(mainButton);
	m_gameObjects.push_back(pause);

	std::cout << "entering PauseState\n";
	return true;
}

bool PauseState::onExit() {
	TheTextureManager::Instance()->clearFromTextureMap("PlayerPause");
	TheTextureManager::Instance()->clearFromTextureMap("Mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("Resumebutton");
	TheTextureManager::Instance()->clearFromTextureMap("Pause");
	std::cout << "exiting PauseState\n";
	return GameState::onExit();
}