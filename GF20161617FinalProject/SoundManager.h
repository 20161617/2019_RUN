#pragma once
#include "SDL.h"
#include <SDL_mixer.h>
#include <map>
#include <iostream>

class SoundManager {
private:
	SoundManager() {};
	static SoundManager* s_pInstance;
	std::map<std::string, Mix_Music*>m_musicMap; //배경음 맵
	std::map<std::string, Mix_Chunk*>m_chunkMap; //효과음 맵

public:
	static SoundManager* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new SoundManager();
		return s_pInstance;
	}
	bool loadSound(std::string fileName, std::string id, std::string kind); //사운드 로드
	void playMusic(std::string id, int count); //배경음 플레이
	void playChunk(int channel, std::string id, int count); //효과음 플레이
	void freeMusic(std::string id); //배경음 초기화
	void freeChunk(std::string id); //효과음 초기화
};
typedef SoundManager TheSoundManager;