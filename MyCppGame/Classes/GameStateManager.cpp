#include "GameStateManager.h"

CGSM::CGSM()
{
	m_eGameState = E_GAME_STATE::E_MENU;
}

CGSM::~CGSM()
{

}

void CGSM::setGameState(E_GAME_STATE newState)
{
	m_eGameState = newState;
}

E_GAME_STATE CGSM::getGameState(void)
{
	return m_eGameState;
}