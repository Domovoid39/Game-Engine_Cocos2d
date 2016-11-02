#ifndef _GEM_H_
#define _GEM_H_

#include <iostream>
#include "cocos2d.h"

#define MAX_HORIZONTAL 10
#define MAX_VERTICAL 10

enum E_GEM_TYPES{
	E_BLUE,
	E_GREEN,
	E_ORANGE,
	E_PURPLE,
	E_RED,
	E_WHITE,
	E_YELLOW,
	E_EMPTY,
	E_TOTAL_TYPE
};

enum E_GEM_STATE {
	E_GEM_NORMAL,
	E_GEM_REMOVE,
	E_GEM_MOVE,
	E_GEM_TOTAL
};

static const char* const g_scGemFileName[E_TOTAL_TYPE] = {
	"Blue.png",
	"Green.png",
	"Orange.png",
	"Purple.png",
	"Red.png",
	"White.png",
	"Yellow.png",
	"Empty.png"
};

class CGems
{
public:	
	cocos2d::Sprite* m_sprite;
	E_GEM_TYPES m_eGemType;
	E_GEM_STATE m_eState;

	cocos2d::Action* m_Action;
	bool m_bDrop;

	CGems();
	~CGems();

	void Init(E_GEM_TYPES newType, USHORT x, USHORT y);
	void Render(USHORT, USHORT);
	void Update(void);
	cocos2d::Sprite* getSprite(void) { return m_sprite; };
	void ChangeTexture(E_GEM_TYPES newtype);

	E_GEM_STATE getState(void) { return m_eState; };
	void setState(E_GEM_STATE eState) { m_eState = eState; };

	E_GEM_TYPES getType(void) { return m_eGemType; };
	void SetType(E_GEM_TYPES newType) { m_eGemType = newType; };

	void SetY(float newY) { m_sprite->setPositionY(newY); };

};

#endif