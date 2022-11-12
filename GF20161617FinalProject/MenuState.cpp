#include "MenuState.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "BackGround.h"

MenuState* MenuState::s_pInstance = NULL;

const std::string MenuState::s_menuID = "MENU";

void MenuState::update() {
	GameState::update();
}

void MenuState::render() {
	dynamic_cast<SDLGameObject*>(m_gameObjects[1])->changeBackgroundState(); //뒷 배경 변수값 변경
	GameState::render();
	//도움말 렌더링
	TheTextManager::Instance()->drawText("Help1", ((TheGame::Instance()->getWindowSize("width") / 2) - (HELP1_TEXT_WIDTH / 2)),
		(TheGame::Instance()->getWindowSize("height") / 2) + HELP1_TEXT_POSY, HELP1_TEXT_WIDTH, HELP_TEXT_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);
	TheTextManager::Instance()->drawText("Help2", ((TheGame::Instance()->getWindowSize("width") / 2) - (HELP2_TEXT_WIDTH / 2)),
		(TheGame::Instance()->getWindowSize("height") / 2) + HELP2_TEXT_POSY, HELP2_TEXT_WIDTH, HELP_TEXT_HEIGHT, TheGame::Instance()->getRenderer(), SDL_FLIP_NONE);

}

bool MenuState::onEnter() {
	//플레이 버튼 로드
	if (!TheTextureManager::Instance()->load("assets/playButton.png", "PlayButton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//나가기 버튼 로드
	if (!TheTextureManager::Instance()->load("assets/exitButton.png", "ExitButton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//배경 로드
	if (!TheTextureManager::Instance()->load("assets/menuBackground.png", "Background", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	//게임 제목 스프라이트 로드
	if (!TheTextureManager::Instance()->load("assets/name.png", "GameName", TheGame::Instance()->getRenderer()))
	{
		return false;
	}


	GameObject* menuBackground1 = new BackGround(new LoaderParams(POS_ZERO, POS_ZERO, 
		TheGame::Instance()->getWindowSize("width"), TheGame::Instance()->getWindowSize("height"), "Background"));
	GameObject* menuBackground2 = new BackGround(new LoaderParams(TheGame::Instance()->getWindowSize("width"), POS_ZERO,
		TheGame::Instance()->getWindowSize("width"), TheGame::Instance()->getWindowSize("height"), "Background"));
	GameObject* playButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + UPSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "PlayButton"), s_menuToPlay);
	GameObject* exitButton = new MenuButton(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (BUTTON_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) + DOWNSIDE_BUTTON_POSY, BUTTON_WIDTH, BUTTON_HEIGHT, "ExitButton"), s_exitFromMenu);
	GameObject* gameName = new BackGround(new LoaderParams((TheGame::Instance()->getWindowSize("width") / 2) - (GAME_NAME_WIDTH / 2),
		(TheGame::Instance()->getWindowSize("height") / 2) - GAME_NAME_POSY, GAME_NAME_WIDTH, GAME_NAME_HEIGHT, "GameName"));

	m_gameObjects.push_back(menuBackground1);
	m_gameObjects.push_back(menuBackground2);
	m_gameObjects.push_back(playButton);
	m_gameObjects.push_back(exitButton);
	m_gameObjects.push_back(gameName);

	//사용키 설명
	TheTextManager::Instance()->loadText("Help1", "Jump : UP", { BLACK, BLACK, BLACK }, TheGame::Instance()->getRenderer());
	TheTextManager::Instance()->loadText("Help2", "Shoot : SPACE", { BLACK, BLACK, BLACK }, TheGame::Instance()->getRenderer());

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit() {
	TheTextureManager::Instance()->clearFromTextureMap("Background");
	TheTextureManager::Instance()->clearFromTextureMap("PlayButton");
	TheTextureManager::Instance()->clearFromTextureMap("ExitButton");
	TheTextureManager::Instance()->clearFromTextureMap("GameName");
	TheTextManager::Instance()->clearFromTextMap("Help1");
	TheTextManager::Instance()->clearFromTextMap("Help2");
	std::cout << "exiting MenuState\n";
	return GameState::onExit();
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}