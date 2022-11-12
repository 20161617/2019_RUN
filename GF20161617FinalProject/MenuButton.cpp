#include "MenuButton.h"
#include "SoundManager.h"

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)())
	: SDLGameObject(pParams), m_callback(callback) 
{
	
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::update() {
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			//마우스가 버튼위에 있는 상황에서 눌렸을 때
			m_currentFrame = CLICKED;
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_currentFrame == CLICKED) 
		{
			//마우스가 버튼위에 있는 상태에서 눌렀다 떼어졌을 때
			m_callback();
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			//마우스가 버튼위에 있는 상황일 때, 눌리지는 않음
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}