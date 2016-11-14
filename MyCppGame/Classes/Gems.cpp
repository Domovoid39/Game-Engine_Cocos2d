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

//plays sprite explosion attached , NOTE: not by sprite sheet, its individual images
void CGems::playExplosion(void)
{
	USHORT spriteFrames = 4;

	Vector<SpriteFrame*> animFrames(spriteFrames);
	char str[100] = { 0 };
	for (int i = 1; i < spriteFrames; i++)
	{
		sprintf(str, "Animations/Explosion_%d.png", i);
		auto frame = SpriteFrame::create(str, Rect(0, 0, 64, 64));
		//SpriteFrame frame = cache->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
	auto animate = Animate::create(animation);
	animation->setRestoreOriginalFrame(true);
	
	auto callback = CallFunc::create([this]() {
		this->ChangeTexture(E_EMPTY);
	});

	cocos2d::CCFiniteTimeAction* animationSequence = cocos2d::CCSequence::create(animate, callback, nullptr);
	m_sprite->runAction(animationSequence);
}