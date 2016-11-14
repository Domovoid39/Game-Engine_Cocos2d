#ifndef __SCENE_INGAME_H__
#define __SCENE_INGAME_H__

#include "cocos2d.h"
#include "Classes\Gems.h"
#include "ui\CocosGUI.h"
#include <string>
#include "GameStateManager.h"


USING_NS_CC;
using namespace std;

//in-game states
enum E_IN_GAME_STATE {
	E_GAME_NORMAL,
	E_GAME_REMOVE,
	E_GAME_CREATE,
	E_GAME_REST,
	E_GAME_TOTAL
};

class Game: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
  
	struct sNode {
		CGems* gem;
	};

	/*CGSM *m_GSM;*/

	sNode **m_arrGem;
	sNode* sNodeSelected1;
	sNode* sNodeSelected2;
	USHORT shNodeX, shNodeY;

	//player Data
	Label* m_TextPlayerscore;
	int m_playerScore;
	Label* m_TextMovesTaken;
	int m_movesTaken;

	E_IN_GAME_STATE m_inGameState;
	float m_fdeltaTime;

	//for debug use 
	Label* m_TextNode1_DEBUG;
	Label* m_TextNode2_DEBUG;

	Game();
	~Game();
	virtual void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void CheckEntireArray(void);
	void RemoveGems(void);
	void ShiftGems(void);
	void CreateGems(void);
	
	bool CheckLowerX(USHORT x, USHORT y);
	bool CheckLowerY(USHORT x, USHORT y);

	virtual void onMouseMove(cocos2d::Event*);
	virtual void onMouseUp(cocos2d::Event*);
	virtual void onMouseDown(cocos2d::Event*);
	virtual void onMouseScroll (cocos2d::Event*);

	void CheckGemTouch(Vec2 touchPoint);
	void SwapGem(void);
	void ChangeGemTexture(void);
	bool CheckSingleGem(USHORT x, USHORT y);

	// implement the "static create()" method manually
    CREATE_FUNC(Game);
};

#endif //__SCENE_INGAME_H__
