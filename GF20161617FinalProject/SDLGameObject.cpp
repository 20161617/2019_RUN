#include "SDLGameObject.h"
#include "Game.h"

int SDLGameObject::speed = START_SPEED;

SDLGameObject::SDLGameObject(const LoaderParams* pParams) :GameObject(pParams), 
m_position(pParams->getX(), pParams->getY()), m_velocity(0,0), m_acceleration(0.0f,0.0f) {
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = RESET;
	m_currentFrame = RESET;
	scrolling = RESET;
	checkBackground = false;
}

void SDLGameObject::update() {
	m_velocity += Vector2D(0, 0);
	m_velocity += m_acceleration;
	m_position += m_velocity;
}
void SDLGameObject::draw() {
	if (m_textureID == "Background" || m_textureID == "Platform" || m_textureID == "Enemy")
	{
		//스크롤을 사용하는 텍스쳐들만 사용
		TextureManager::Instance()->drawBackground(m_textureID, scrolling, checkBackground, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
			m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
	}
	else
	{
		TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(),
			(Uint32)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}
}