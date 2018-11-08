#ifndef HAND_CARD_LAYER_H
#define HAND_CARD_LAYER_H

#include "cocos2d.h"
USING_NS_CC;

#include "DemoCard\SpriteCardManage.h"

class GameLayer;
class SelfHandCard :public SpriteCardManage
{   
public:
    SelfHandCard(GameLayer *pGameLayer);
    virtual ~SelfHandCard();
	
	int GetRandSendCard(int *iCardIndex);

	void ShowSendBtn(bool bShow);
private:
	GameLayer *m_pGameLayer;

	virtual void onEnter();				
	virtual void onExit();			
	
	virtual void ResetAllCardPosition();
	
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);		
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);		
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);		

	int m_iTouchesBeganCardIndex;		//触摸按下所在的牌索引位置
	
	CCMenuItemImage *m_pBtnSend;
	void OnBtnSend(CCObject *pBtn);	
};

#endif
