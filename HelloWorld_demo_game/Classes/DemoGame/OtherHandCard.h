#ifndef OTHER_HAND_CARD_H
#define OTHER_HAND_CARD_H

#include "cocos2d.h"
USING_NS_CC;

#include "DemoCard\SpriteCardManage.h"

class OtherHandCard :public SpriteCardManage
{   
public:
    OtherHandCard(int iTablePos);
    virtual ~OtherHandCard();
	
	int GetRandSendCard(int *iCardIndex);
private:
	int m_iTablePos;

	CCLabelAtlas *m_pLableLeftNum;
	
	virtual void ResetAllCardPosition();

	virtual void onEnter();				
	virtual void onExit();
};

#endif
