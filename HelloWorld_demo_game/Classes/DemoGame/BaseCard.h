#ifndef BASE_CARD_H
#define BASE_CARD_H

#include "cocos2d.h"
USING_NS_CC;

#include "DemoCard\SpriteCardManage.h"

class BaseCard :public SpriteCardManage
{   
public:
    BaseCard();
    virtual ~BaseCard();
	
private:
	virtual void ResetAllCardPosition();

};

#endif
