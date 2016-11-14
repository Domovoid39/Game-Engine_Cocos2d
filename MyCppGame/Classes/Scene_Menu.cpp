#include "Scene_Menu.h"
#include "SimpleAudioEngine.h"


MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{	
	
}

Scene* MainMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	//For mouse input
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MainMenu::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(MainMenu::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(MainMenu::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	////for Touch input
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = CC_CALLBACK_1(MainMenu::onMouseDown, this);
	//touchListener->onTouchEnded = CC_CALLBACK_1(MainMenu::onMouseDown, this);
	//touchListener->onTouchMoved = CC_CALLBACK_1(MainMenu::onMouseMove, this);
	//
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	m_playButton = Button::create("MainMenu/button_play.png", "MainMenu/button_play_pressed.png");
	//m_playButton->addClickEventListener(CC_CALLBACK_1(MainMenu::ToGamePlay, this));
	m_playButton->addTouchEventListener(CC_CALLBACK_2(MainMenu::ToGamePlay, this));
	m_playButton->setPosition(Vec2(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f));
	this->addChild(m_playButton);


	//start the update
	this->scheduleUpdate();

	return true;
}

void MainMenu::onMouseMove(cocos2d::Event* _event)
{
	
}
void MainMenu::onMouseUp(cocos2d::Event* _event)
{

}
void MainMenu::onMouseDown(cocos2d::Event* _event)
{
	EventMouse *e = (EventMouse*)_event;
	Vec2 touchPoint = Vec2(e->getCursorX(), e->getCursorY());
	//CheckGemTouch(touchPoint);
}
void MainMenu::onMouseScroll(cocos2d::Event* _event)
{

}

void MainMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}

/*
This function is called every frame
* @param : dt : delta time - time inbetween each frame
*/
void MainMenu::update(float dt)
{
	
}

void MainMenu::ToGamePlay(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
		break;

	case ui::Widget::TouchEventType::ENDED:
		//replace the scene with the game scene
		auto scene = Game::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));

		break;
	}
}