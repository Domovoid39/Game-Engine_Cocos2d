#ifndef _GSM_H_
#define _GSM_H_

#include <iostream>
#include "cocos2d.h"

//game states
enum E_GAME_STATE {
	E_GAME_NORMAL,
	E_GAME_REMOVE,
	E_GAME_CREATE,
	E_GAME_REST,
	E_GAME_TOTAL
};

class CGSM
{
public:

	CGSM();
	~CGSM();
	E_GAME_STATE m_eGameState;
	float m_fdeltatime;

	void UpdateGSM(float dt);

	void setGameState(E_GAME_STATE newState);
	E_GAME_STATE getGameState(void);
};

#endif