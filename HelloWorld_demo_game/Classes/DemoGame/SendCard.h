#ifndef SEND_CARD_H
#define SEND_CARD_H

#include "cocos2d.h"
USING_NS_CC;

#include "DemoCard\SpriteCardManage.h"


class SendCard :public SpriteCardManage
{   
public:
    SendCard(int iTablePos);
    virtual ~SendCard();
	
private:
	int m_iTablePos;
	virtual void ResetAllCardPosition();
};

#endif
