#include "TextureManager.h"
TextureManager* TextureManager::s_pInstance = 0;

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = POS_ZERO;
	srcRect.y = POS_ZERO;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawBackground(std::string id, int scrolling, bool checkBackground, int x, int y, int width, int height, int currentRow, int currentFrame,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	//스크롤을 사용하는 텍스쳐들이 사용
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow - 1;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	if (checkBackground == false)
	{
		if (id == "Background" ||  x <= 0) //배경이 창의 왼쪽 밖으로 나갔다면
		{ 
			destRect.x = -scrolling; //그만큼 나가서 그려줌
		}
		else
		{
			destRect.x = x; 
		}
	}
	else
	{
		destRect.x = -scrolling + width;
		
	}
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
	SDL_Renderer* pRenderer, SDL_RendererFlip flip) {

	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow - 1;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}