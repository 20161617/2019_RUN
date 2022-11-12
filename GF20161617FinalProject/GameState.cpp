#include "GameState.h"
#include "GameObject.h"

void GameState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void GameState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool GameState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	return true;
}