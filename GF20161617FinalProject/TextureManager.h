#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <map>
#include "GameEnum.h"

class TextureManager {
private:
	TextureManager() {};
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*>m_textureMap;

public:
	static TextureManager* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new TextureManager();
		return s_pInstance;
	}
	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//스크롤 되는 모든 것들에 사용
	void drawBackground(std::string id, int scrolling, bool checkBackground, int x, int y, int width, int height, int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
		SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void clearFromTextureMap(std::string id);
};
typedef TextureManager TheTextureManager;