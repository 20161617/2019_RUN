#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) {
				if (TTF_Init() == -1) //SDL_TTF 초기화
				{
					return false;
				}
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
				m_pGameStateMachine = new GameStateMachine();
				m_pGameStateMachine->changeState(MenuState::Instance());
				if (flags != (result = Mix_Init(flags))) { //SDL_MIXER 초기화
					printf("Could not initialize mixer (result: %d).\n", result);
					printf("Mix_Init: %s\n", Mix_GetError());
					return false;
				}
				Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
				if (!TheSoundManager::Instance()->loadSound("Assets/BGM.mp3", "BGM", "music")) //배경음 로드
				{
					return false;
				}
				TheSoundManager::Instance()->playMusic("BGM", NONSTOP); //배경을 플레이 무한 반복
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
	m_bRunning = true;
	return true;
}

void Game::render() {
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::handleEvents() {
	TheInputHandler::Instance()->update();
}

void Game::update() {
	m_pGameStateMachine->update();
}
void Game::clean() {
	TheInputHandler::Instance()->update();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheSoundManager::Instance()->freeMusic("BGM");
	TheTextManager::Instance()->~TextManager();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}