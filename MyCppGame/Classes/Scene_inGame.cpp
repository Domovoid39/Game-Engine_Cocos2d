#include "Scene_inGame.h"
#include "SimpleAudioEngine.h"

Game::Game()
{
	m_arrGem = nullptr;
}
Game::~Game()
{	
	for (int i = 0; i < MAX_HORIZONTAL; i++)
	{
		for (int j = 0; j < MAX_VERTICAL; j++)
		{
			delete m_arrGem[i][j].gem;
			m_arrGem[i][j].gem = nullptr;
		}
	}
}

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
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
		CC_CALLBACK_1(Game::menuCloseCallback, this));

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

	auto label = Label::createWithTTF("GAME", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	m_arrGem = new sNode*[MAX_HORIZONTAL];

	for (int i = 0; i < MAX_HORIZONTAL; i++)
	{
		m_arrGem[i] = new sNode[MAX_VERTICAL];
		for (int j = 0; j < MAX_VERTICAL; j++)
		{
			m_arrGem[i][j].gem = new CGems();
		}
	}


	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			m_arrGem[i][j].gem->Init((E_GEM_TYPES)(INT)(CCRANDOM_0_1() *(E_TOTAL_TYPE - 1)), i, j);
			
			//making sure the gems to find a mtach during startup
			if (!CheckLowerX(i, j) || !CheckLowerY(i, j))
				j--;
			else  //if no same then add into render list
				this->addChild(m_arrGem[i][j].gem->getSprite(), 0);			
		}
	}

	m_fdeltaTime = 0.0f;
	m_inGameState = E_IN_GAME_STATE::E_GAME_NORMAL;

	sNodeSelected1 = nullptr;
	sNodeSelected2 = nullptr;
	shNodeY = shNodeX = 0;

	m_TextPlayerscore = Label::createWithTTF("PlayerScore", "fonts/Marker Felt.ttf", 24);
	m_TextPlayerscore->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.5));
	this->addChild(m_TextPlayerscore);
	m_playerScore = 0;
	
	m_TextMovesTaken = Label::createWithTTF("Moves Taken", "fonts/Marker Felt.ttf", 24);
	m_TextMovesTaken->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.8));
	this->addChild(m_TextMovesTaken);
	m_movesTaken = 0;

	m_TextNode1_DEBUG = Label::createWithTTF("Node1 selected", "fonts/Marker Felt.ttf", 24);
	m_TextNode1_DEBUG->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.4));
	this->addChild(m_TextNode1_DEBUG);
	
	m_TextNode2_DEBUG = Label::createWithTTF("Node2 Selected", "fonts/Marker Felt.ttf", 24);
	m_TextNode2_DEBUG->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.3));
	this->addChild(m_TextNode2_DEBUG);
	
	//For mouse input
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Game::onMouseUp, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(Game::onMouseDown, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(Game::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	////for Touch input
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = CC_CALLBACK_1(Game::onMouseDown, this);
	//touchListener->onTouchEnded = CC_CALLBACK_1(Game::onMouseDown, this);
	//touchListener->onTouchMoved = CC_CALLBACK_1(Game::onMouseMove, this);
	//
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//start the update
	this->scheduleUpdate();

	return true;
}

void Game::onMouseMove(cocos2d::Event* _event)
{
	
}
void Game::onMouseUp(cocos2d::Event* _event)
{

}
void Game::onMouseDown(cocos2d::Event* _event)
{
	EventMouse *e = (EventMouse*)_event;
	Vec2 touchPoint = Vec2(e->getCursorX(), e->getCursorY());
	CheckGemTouch(touchPoint);
}
void Game::onMouseScroll(cocos2d::Event* _event)
{

}

void Game::menuCloseCallback(Ref* pSender)
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

void Game::update(float dt)
{
	//m_GSM->UpdateGSM(dt);
	m_fdeltaTime += dt;

	stringstream convertingScore;
	convertingScore << m_playerScore;
	m_TextPlayerscore->setString("PlayerScore: " + convertingScore.str() );
	
	stringstream movesTaken;
	movesTaken << m_movesTaken;
	m_TextMovesTaken->setString("Moves taken: " + movesTaken.str());

	//based on time loop - change when match the minimum time requirements
	if (m_fdeltaTime > 0.5f)
	{
		switch (m_inGameState)
		{
		case E_GAME_NORMAL:
			CheckEntireArray();
			break;
		case E_GAME_CREATE:
			//CreateGems();
			ShiftGems();
			break;
		case E_GAME_REMOVE:
			RemoveGems();
			break;
		case E_GAME_REST:
			m_inGameState = E_GAME_NORMAL;
			break;
		}

		m_fdeltaTime = 0.0f;
	}
}

void Game::CheckEntireArray(void)
{
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
		for (int j = 0; j < MAX_VERTICAL; ++j) {
			if (!CheckLowerX(i, j)) {
				for (int k = 0; k < 3; k++) {
					m_arrGem[i - k][j].gem->setState(E_GEM_REMOVE);
				}
				m_inGameState = E_IN_GAME_STATE::E_GAME_REMOVE;
			}
			if (!CheckLowerY(i, j)) {
				for (int k = 0; k < 3; k++) {
					m_arrGem[i][j - k].gem->setState(E_GEM_REMOVE);
				}
				m_inGameState = E_IN_GAME_STATE::E_GAME_REMOVE;
			}
		}
}

void Game::RemoveGems(void)
{
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
	{
		for (int j = 0; j < MAX_VERTICAL; ++j)
		{
			if (m_arrGem[i][j].gem->getState() == E_GEM_REMOVE)
			{
				if (m_arrGem[i][j].gem->getType() != E_EMPTY)
				{
					m_playerScore += 1;
					m_arrGem[i][j].gem->playExplosion();
				}
			}
		}
	}
	
	sNodeSelected1 = nullptr;
	sNodeSelected2 = nullptr;
	
	m_inGameState = E_IN_GAME_STATE::E_GAME_CREATE;
}

void Game::ShiftGems(void)
{
	USHORT shCur;
	for (int i = 0; i < MAX_HORIZONTAL; ++i) {
		shCur = MAX_VERTICAL;
		for (int j = MAX_VERTICAL - 1; j >= 0; --j) {
			if (m_arrGem[i][j].gem->getState() == E_GEM_REMOVE)
			{
				if (shCur == MAX_VERTICAL)
					shCur = j;
			}
			else {
				if (shCur != MAX_VERTICAL)
				{
					m_arrGem[i][shCur].gem->ChangeTexture(m_arrGem[i][j].gem->getType());
					m_arrGem[i][shCur].gem->setState(E_GEM_NORMAL);
					m_arrGem[i][j].gem->ChangeTexture(E_EMPTY);
					m_arrGem[i][j].gem->setState(E_GEM_REMOVE);
					if (m_arrGem[i][shCur - 1].gem->getState() == E_GEM_REMOVE)
						shCur--;
					else
						shCur = j;
				}
			}
		}
	}

	CreateGems();
}

void Game::CreateGems(void)
{
	for (int i = 0; i < MAX_HORIZONTAL; ++i)
		for (int j = 0; j < MAX_VERTICAL; ++j)
			if (m_arrGem[i][j].gem->getState() == E_GEM_REMOVE) {
				m_arrGem[i][j].gem->ChangeTexture((E_GEM_TYPES)(INT)(CCRANDOM_0_1()*(E_TOTAL_TYPE -1)));
				m_arrGem[i][j].gem->setState(E_GEM_NORMAL);
			}
	//ShiftGems();
	m_inGameState = E_IN_GAME_STATE::E_GAME_REST;
}

bool Game::CheckLowerX(USHORT x, USHORT y)
{
	if (x < 2)
		return true;
	for (int i  = 1; i < 3; i++)
	{
		if (m_arrGem[x][y].gem->getType() != m_arrGem[x - i][y].gem->getType()) 
			return true;
	}
	return false;
}

bool Game::CheckLowerY(USHORT x, USHORT y )
{
	if (y < 2) return true;
	for (int i  = 1; i < 3; i++)
	{
		if (m_arrGem[x][y].gem->getType() != m_arrGem[x][y - i].gem->getType() ) 
			return true;
	}
	return false;
}

void Game::CheckGemTouch(Vec2 touchPoint)
{
	if (m_inGameState != E_IN_GAME_STATE::E_GAME_NORMAL)
		return;

	int i , j = 0;
	bool bContain = false;
	for ( i = 0; i < MAX_HORIZONTAL; i++)
	{
		for (j = 0; j < MAX_VERTICAL; j++)
		{
			Sprite* curSprite = m_arrGem[i][j].gem->getSprite();
			if (curSprite->getBoundingBox().containsPoint(touchPoint))
			{
				bContain = true;
				break;
			}
		}
		if (bContain)
		{
			break;
		}
	}

	if (!bContain)
		return;

	assert(i != MAX_HORIZONTAL && j != MAX_VERTICAL);

	if (sNodeSelected1 != nullptr)
	{
		if (&m_arrGem[i][j] == sNodeSelected1)
			return;
		else
		{
			sNodeSelected2 = &m_arrGem[i][j];
			SwapGem();

			/* ---------------------------
			=> DEBUG TEXT - showing the gem coord
			----------------------------- */
			stringstream temp_gemPos;
			temp_gemPos << i << ", " << j;
			m_TextNode2_DEBUG->setString("Gem 2: " + temp_gemPos.str());

			//the numbers of gems between the 1st and 2nd click
			int pos_X = shNodeX - i;
			int pos_Y = shNodeY - j;

			//swapping gems back if they are not next to the first selected gem
			if(pos_X < -1 || pos_X > 1 || pos_Y < -1 || pos_Y > 1)
				SwapGem();
			
			//check if got move diagonal within 1 gem radius then swap back
			if (pos_X <= 1 && pos_X >= -1 && pos_Y <= 1 && pos_Y >= -1 && (pos_X != 0 && pos_Y != 0))
				SwapGem();
			
			//reset the stored 
			sNodeSelected1 = nullptr;
			sNodeSelected2 = nullptr;
			shNodeX = shNodeY = 0;

			m_movesTaken += 1;
		}
	}
	else
	{
		sNodeSelected1 = &m_arrGem[i][j];
		shNodeX = i;
		shNodeY = j;

		/* ---------------------------
		=> DEBUG TEXT - showing the gem coord
		----------------------------- */
		stringstream temp_gemPos;
		temp_gemPos << shNodeX << ", " << shNodeY;
		m_TextNode1_DEBUG->setString("Gem 1: " + temp_gemPos.str());

		m_TextNode2_DEBUG->setString("Gem 2: -, -");
	}
}

void Game::SwapGem(void)
{
	E_GEM_TYPES eGemType = sNodeSelected2->gem->getType();
	sNodeSelected2->gem->ChangeTexture(sNodeSelected1->gem->getType());
	sNodeSelected1->gem->ChangeTexture(eGemType);
}

void Game::ChangeGemTexture(void)
{
	/*E_GEM_TYPES eGemType = sNodeSelected2->gem->getType();
	sNodeSelected2->gem->ChangeTexture(sNodeSelected1->gem->getType());
	sNodeSelected1->gem->ChangeTexture(eGemType);*/
}

bool Game::CheckSingleGem(USHORT x, USHORT y)
{
	for (int i = 0; i < MAX_HORIZONTAL; i++)
	{
		if (!CheckLowerX(i, y))
			return true;
	}

	for (int i = 0; i < MAX_VERTICAL; i++)
	{
		if (!CheckLowerY(x, i))
			return true;
	}

	return false;
}