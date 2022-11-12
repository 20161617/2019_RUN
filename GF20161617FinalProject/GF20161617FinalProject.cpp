#include "Game.h"

int main(int argc, char* argv[]) {
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;
	if (TheGame::Instance()->init("FinalProject", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, false)) {
		Uint32 frameStart, frameTime;
		while (TheGame::Instance()->running()) {
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME) {
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else {
		std::cout << "game init failure" << SDL_GetError() << "\n";
		return -1;
	}

	TheGame::Instance()->clean();
	return 0;
}


