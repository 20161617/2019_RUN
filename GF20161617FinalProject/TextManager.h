#pragma once
#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include "GameEnum.h"

using namespace std;

class TextManager {
private:
	TextManager() { m_font = TTF_OpenFont("Assets/neodgm.ttf", 28); } //폰트 로드 글자크기 28
	static TextManager* s_pInstance;
	TTF_Font* m_font; //폰트
	std::map<std::string, SDL_Texture*>m_textMap; //텍스트 맵 배열
public:
	~TextManager() { TTF_CloseFont(m_font); }
	static TextManager* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new TextManager();
		return s_pInstance;
	}
	bool loadText(std::string id, std::string textureText, SDL_Color textColor, SDL_Renderer* pRenderer); //텍스트 로드
	void drawText(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip); //텍스트 출력
	void clearFromTextMap(std::string id); //텍스트 초기화
};
typedef TextManager TheTextManager;
