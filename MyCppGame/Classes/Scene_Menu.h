#ifndef __SCENE_MENU_H__
#define __SCENE_MENU_H__

#include "cocos2d.h"
#include "Classes\Gems.h"
#include "ui\CocosGUI.h"
#include <string>
#include "GameStateManager.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;
using namespace ui;

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	Button* m_playButton;

	virtual bool init();

	MainMenu();
	~MainMenu();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual void onMouseMove(cocos2d::Event*);
	virtual void onMouseUp(cocos2d::Event*);
	virtual void onMouseDown(cocos2d::Event*);
	virtual void onMouseScroll(cocos2d::Event*);

	void ToGamePlay(Ref *pSender, Widget::TouchEventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif // __SCENE_MENU_H__
