#ifndef _GSM_H_
#define _GSM_H_

#include <iostream>
#include "cocos2d.h"
#include "Scene_inGame.h"
#include "Scene_Menu.h"

//game states
enum E_GAME_STATE {
	E_MENU,
	E_INGAME,
	E_OPTIONS,
	E_TOTAL,
};

class CGSM
{
public:
	CGSM();
	~CGSM();
	E_GAME_STATE m_eGameState;
	
	void setGameState(E_GAME_STATE newState);
	E_GAME_STATE getGameState(void);
};

#endif