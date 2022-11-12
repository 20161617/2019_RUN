#include "TextManager.h"

TextManager* TextManager::s_pInstance = 0;

bool TextManager::loadText(std::string id, std::string textureText, SDL_Color textColor, SDL_Renderer* pRenderer)
{
	//텍스트 로드, 폰트 및 색상 설정
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, textureText.c_str(), textColor);
	if (textSurface == NULL) //로드가 되지 않았을 시 faㅣse 리턴
	{
		printf("Unable to render text surface!");
		return false;
	}
	else
	{
		//텍스쳐 생성
		SDL_Texture* m_texture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
		if (m_texture == NULL) //텍스쳐 생성이 되지 않았을 시 false리턴
		{
			printf("Unable to create texture from rendered text");
			return false;
		}
		else
		{
			//생성이 되었다면 저장
			m_textMap[id] = m_texture;
			return true;
		}
		SDL_FreeSurface(textSurface); //해제
	}

	return m_textMap[id] != NULL;
}

void TextManager::drawText(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	//텍스트 그리기
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = POS_ZERO;
	srcRect.y = POS_ZERO;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextManager::clearFromTextMap(std::string id) //텍스트 초기화
{
	SDL_DestroyTexture(m_textMap[id]);
	m_textMap.erase(id);
}