#ifndef __HAND_CARD_LAYER_H__
#define __HAND_CARD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SpriteCardManage.h"

class DealCardLayer;
class HandCardLayer : public SpriteCardManage
{
public:
	HandCardLayer(DealCardLayer *pDealCardLayer);

	virtual ~HandCardLayer();

private:
	DealCardLayer *m_pDealCardLayer;

	virtual void onEnter();

	virtual void onExit();

	virtual void ResetAllCardPosition();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	int m_iTouchesBeganCardIndex;	//触摸按下所在的牌索引位置

	CCMenuItemImage *m_pBtnSend;

	void OnBtnSend(CCObject *pBtn);
};

#endif

