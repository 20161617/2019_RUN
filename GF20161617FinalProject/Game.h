#pragma once
#include "TextureManager.h"
#include "SoundManager.h"
#include "TextManager.h"

class GameStateMachine;

class Game {
private:
	Game() { result = 0; }
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	GameStateMachine* m_pGameStateMachine;
	
	int windowWidth;
	int windowHeight;

	bool m_bRunning;	

	//사운드 관련 변수
	int result;
	int flags = MIX_INIT_MP3;

public:
	static Game* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer()const { return m_pRenderer; }

	GameStateMachine* getStateMachine()
	{
		return m_pGameStateMachine;
	}

	int getWindowSize(std::string name) { //width입력시 폭 반환, height입력시 높이 반환
		SDL_GetWindowSize(m_pWindow, &windowWidth, &windowHeight); //윈도우 크기 구하는 SDL 함수
		if (name == "width")
		{
			return windowWidth; //넓이 반환
		}
		else if (name == "height")
		{
			return windowHeight; //높이 반환
		}
		std::cout << "입력값 오류 크기 반환 안됨\n";
		return 0;
	}

	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	bool running() { return m_bRunning; }
	void handleEvents();
	void clean();
	void quit() { m_bRunning = false; }
};
typedef Game TheGame;