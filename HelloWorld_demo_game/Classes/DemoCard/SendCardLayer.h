#ifndef __SEND_CARD_LAYER_H__
#define __Send_CARD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SpriteCardManage.h"

class SendCardLayer : public SpriteCardManage
{
public:
	SendCardLayer();

	virtual ~SendCardLayer();

	void ResetAllCardPosition();
};

#endif

