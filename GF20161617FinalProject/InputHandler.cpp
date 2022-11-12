#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;
InputHandler::InputHandler() {
	m_mousePosition = new Vector2D(0, 0);
	for (int i = 0; i < 3; i++) {
		m_mouseButtonStates.push_back(false);
	}
	for (int i = 0; i < 100; i++) { //키보드 눌림을 확인하는 배열을 false로 초기화
		checkKeyState.push_back(false); //A = 4부터 키패드 SDL_SCANCODE_KP_PERIOD = 99까지 약 100개 존재 SDL_scancode참조
	}
}
void InputHandler::clean() {}
void InputHandler::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp();
			break;
		default:
			break;
		}
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber) {
	return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition() {
	return m_mousePosition;
}

bool InputHandler::isKeyOneDown(SDL_Scancode key) {
	if (m_keystates != 0) {
		if (m_keystates[key] == 1 && checkKeyState[key] == false) {//키가 눌려있고 배열의 상태가 눌리지 않은 상태면
			checkKeyState[key] = true;// 눌린상태로 변경
			return true;
		}
		else if (m_keystates[key] == 0 && checkKeyState[key] == true) {// 키가 눌려있지 않고 배열의 상태가 눌려있다면
			checkKeyState[key] = false;// 눌리지 않은 상태로 변경
			return false;
		}
	}
	return false;
}

bool InputHandler::isKeyDown(SDL_Scancode key) {
	if (m_keystates != 0) {
		if (m_keystates[key] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void InputHandler::onKeyDown()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event event)
{
	if (event.type == SDL_MOUSEMOTION) {
		m_mousePosition->setX(event.motion.x);
		m_mousePosition->setY(event.motion.y);
	}
}

void InputHandler::onMouseButtonDown(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_mouseButtonStates[LEFT] = true;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			m_mouseButtonStates[MIDDLE] = true;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_mouseButtonStates[RIGHT] = true;
		}
	}
}

void InputHandler::onMouseButtonUp(SDL_Event event)
{
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_LEFT) {
			m_mouseButtonStates[LEFT] = false;
		}
		if (event.button.button == SDL_BUTTON_MIDDLE) {
			m_mouseButtonStates[MIDDLE] = false;
		}
		if (event.button.button == SDL_BUTTON_RIGHT) {
			m_mouseButtonStates[RIGHT] = false;
		}
	}
}