#ifndef _INPUTS_H_
#define _INPUTS_H_

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//game states
enum E_INPUT_CONTROLS{
	IC_PRIMARY_DOWN,
	IC_PRIMARY_UP,
	IC_SECONDARY_DOWN,
	IC_SECONDARY_UP,
	IC_MOVE,
	IC_NONE,
	IC_TOTAL
};

class CInput	:	public cocos2d::Layer
{
public:

	E_INPUT_CONTROLS currentInput;

	CInput();
	~CInput();	

	void switchState(E_INPUT_CONTROLS newInput);

	void Update(void);

	E_INPUT_CONTROLS getCurrentInput(void);
};

#endif