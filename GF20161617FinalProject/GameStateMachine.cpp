#include "GameStateMachine.h"

void GameStateMachine::popState() {
	changeState(m_prevState);
}

void GameStateMachine::changeState(GameState* pState) {
	if (pState != NULL)
	{
		if (pState->getStateID() == "PAUSE") 
		{ 
		    //바뀔 상태가 일시정시 상태라면 플레이 상태의 정보를 지워서는 안되므로
		    //이전과 현재 스테이트 값을 바꾸기만 한 후 바꿀 상태로 진입한다.
			m_prevState = m_currentState;
			m_currentState = pState;
			m_currentState->onEnter();
		}
		else if (pState->getStateID() == "PLAY" && m_currentState->getStateID() == "PAUSE")
		{
			//현재 일시정지 상태이고 RESUME버튼을 눌러 다시 게임을 재개한다면
			//현재 상태인 일시정지의 상태만 삭제하고 플레이 상태로 변경한다
			m_currentState->onExit();
			m_currentState = pState;
		}
		else if (m_prevState != NULL && pState->getStateID() == "MENU" && m_currentState->getStateID() == "PAUSE")
		{
			//게임이 켜지자 마자 실행이 된다면 이전상태가 없어 에러가 발생하므로 이전상태가 있다는 조건하에
			//일시정지상태에서 메뉴상태로 간다면, 일시정지 상태 이전인 플레이 상태를 제거하고 현재상태인 일시정지상태도 제거한후 메뉴상태로 진입한다.
			m_prevState->onExit();
			m_prevState = m_currentState;
			m_currentState->onExit();
			m_currentState = pState;
			m_currentState->onEnter();
		}
		else 
		{
			//그 외의 상황에서는 똑같이 현재상태 삭제후 바뀔 상태로 진입한다
			if (m_currentState != NULL)
			{
				m_prevState = m_currentState;
				m_currentState->onExit();
			}
			m_currentState = pState;
			m_currentState->onEnter();
		}
	}

}

void GameStateMachine::update() {
	if (m_currentState != NULL)
		m_currentState->update();
}

void GameStateMachine::render() {
	if (m_currentState != NULL)
		m_currentState->render();
}