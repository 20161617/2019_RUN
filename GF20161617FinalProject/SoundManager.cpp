#include "SoundManager.h"

SoundManager* SoundManager::s_pInstance = 0;

bool SoundManager::loadSound(std::string fileName, std::string id, std::string kind) 
{
	//효과음이냐 배경음이냐에 따라 저장되는 위치가 다름 배경음일때 Music 효과음일 때 Chunk
	if (kind == "music")
	{
		m_musicMap[id] = Mix_LoadMUS(fileName.c_str());
		return true;
	}
	else if (kind == "chunk")
	{
		m_chunkMap[id] = Mix_LoadWAV(fileName.c_str());
		return true;
	}
	return false;
}

void SoundManager::playMusic(std::string id, int count) //배경음 재생
{
	Mix_PlayMusic(m_musicMap[id], count);
}

void SoundManager::playChunk(int channel, std::string id, int count) //효과음 재생, 채널설정필수
{
	Mix_PlayChannel(channel, m_chunkMap[id], count);
}

void SoundManager::freeMusic(std::string id) //배경음 초기화
{
	Mix_FreeMusic(m_musicMap[id]);
	m_musicMap.erase(id);
}

void SoundManager::freeChunk(std::string id) //효과음 초기화
{
	Mix_FreeChunk(m_chunkMap[id]);
	m_chunkMap.erase(id);
}