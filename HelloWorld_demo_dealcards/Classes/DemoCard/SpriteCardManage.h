#ifndef __SPRITE_CARD_MANAGE_H__
#define __SPRITE_CARD_MANAGE_H__

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

typedef struct SpriteCard
{
	int iCardIndex;
	int iX;
	int iY;
	int iZ;
	float fScale;
	float fAngle;
	bool bSelected;
	bool bShadow;
	bool bBack;
	CCSprite *pSpriteCard;
	CCSprite *pSpriteShadow;
}SpriteCardDef;

class SpriteCardManage : public CCLayer
{
public:
	SpriteCardManage();

	virtual ~SpriteCardManage();

	SpriteCardDef* AddCard(int iCardIndex, bool bBack = false, bool bSelected = false, bool bReorder = true);	//添加牌

	void ReorderCard();		//由大到小排序

	int GetCardCount(){ return m_vcSpriteCard.size(); }	//获取牌张数目

	void ResetAllSelectCard();	//重置所有选中牌

	void ShowBackSingleCard(SpriteCardDef *pCard, bool bBack);	//设置单张牌的牌背属性，如果要给原本没有值的牌背赋值并且正常显示的话，则在外部就需要改变pCard->iCardIndex

	void ShowBackAllCard(bool bBack);	//设置所有的牌的牌背属性

	void RemoveCard(int iCardIndex, bool bReorder = true);	//删除牌
	
	void RemoveCard(SpriteCardDef *pCard, bool bReorder = true);	//通过指针删除牌
	
	void RemoveAllCard();	//删除所有牌

	void SetNeedShadow(bool bNeed){ m_bNeedShadow = bNeed; }		//设置需要开启阴影

protected:
	virtual void onEnter();

	virtual void onExit();

	vector<SpriteCardDef*> m_vcSpriteCard;

	bool m_bNeedShadow;

	static int CheckCardValue(int iCardNum);

	virtual void ResetAllCardPosition(){};						//重置牌位置，需要实际重载实现
};

#endif

