#include "Inputs.h"

CInput::CInput()
{
	//auto mouseListener = EventListenerMouse::create();
	//mouseListener->onMouseMove = CC_CALLBACK_0(CInput::switchState,E_INPUT_CONTROLS::IC_MOVE, this);
	//mouseListener->onMouseUp = CC_CALLBACK_0(CInput::switchState, E_INPUT_CONTROLS::IC_PRIMARY_UP, this);
	//mouseListener->onMouseDown = CC_CALLBACK_0(CInput::switchState, E_INPUT_CONTROLS::IC_PRIMARY_DOWN, this);
	////mouseListener->onMouseScroll = CC_CALLBACK_0(HelloWorld::onMouseScroll, this);

	//_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}
CInput::~CInput()
{
}

void CInput::switchState(E_INPUT_CONTROLS newInput)
{
	currentInput = newInput;
}
