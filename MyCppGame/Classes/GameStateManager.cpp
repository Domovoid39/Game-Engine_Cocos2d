#include "GameStateManager.h"

CGSM::CGSM()
{
	m_eGameState = E_GAME_NORMAL;
	m_fdeltatime = 0.0f;
}
CGSM::~CGSM()
{
}

void CGSM::UpdateGSM(float dt)
{
	m_fdeltatime += dt;

	/*switch (m_eGameState) {
	case E_GAME_NORMAL:
		
		break;
	case E_GAME_REMOVE:
		if (m_fdeltatime > 1.0f) {
			m_fdeltatime = 0;
		}
		break;
	case E_GAME_CREATE:
		if (m_fdeltatime > 1.0f) {
			m_fdeltatime = 0;
		}
		break;
	case E_GAME_REST:
		if (m_fdeltatime > 1.0f) {
			m_eGameState = E_GAME_NORMAL;
			m_fdeltatime = 0;
		}
		break;
	default:
		m_eGameState = E_GAME_NORMAL;
		break;
	}*/
}

void CGSM::setGameState(E_GAME_STATE newState)
{
	if (m_fdeltatime > 0.5f) {
		m_fdeltatime = 0;
		if (newState == E_GAME_REST)
			newState = E_GAME_NORMAL;
		m_eGameState = newState;
	}
}

E_GAME_STATE CGSM::getGameState(void)
{
	 return m_eGameState; 
}