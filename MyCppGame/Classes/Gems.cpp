#include "Gems.h"

#define MAX_HORIZONTAL 10
#define MAX_VERTICAL 10

USING_NS_CC;

CGems::CGems()
{
	m_eGemType = E_BLUE;
}
CGems::~CGems()
{

}

void CGems::Init(E_GEM_TYPES newType, USHORT x, USHORT y)
{
	m_eGemType = newType;
	m_sprite = cocos2d::Sprite::create(g_scGemFileName[newType]);
	m_eState = E_GEM_NORMAL;

	m_bDrop = false;
	Render(x, y);
}

void CGems::Render(USHORT x, USHORT y)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	float f_posX = (x + 1) * 64;// visibleSize.width / 2 + (x - 5) * 60 + 30;
	float f_posY = visibleSize.height / 2 - (y - 4) * 64 + 32; //visibleSize.height / 2 + (y - 4) * 60 + 30;
	m_sprite->setPosition(cocos2d::Point(f_posX, f_posY));

	m_eState = E_GEM_NORMAL;
}

void CGems::ChangeTexture(E_GEM_TYPES newtype)
{
	m_eGemType = newtype;
	m_sprite->setTexture(g_scGemFileName[newtype]);
}

void CGems::Update(void)
{
}