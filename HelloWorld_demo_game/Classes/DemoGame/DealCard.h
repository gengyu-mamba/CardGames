#ifndef DEAL_CARD_H
#define DEAL_CARD_H

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

#include "DemoCard\SpriteCardManage.h"

class GameLayer;
class DealCard :public SpriteCardManage
{   
public:
    DealCard(GameLayer *pGameLayer,vector<int> vcAllCard,SpriteCardManage **pHandCard,SpriteCardManage *pBaseCard);
    virtual ~DealCard();

private:
	virtual void ResetAllCardPosition();

	virtual void onEnter();
    virtual void onExit();
	virtual void update(float dt);			

	vector<int> m_vcAllCard;

	SpriteCardManage **m_pHandCard;             //4个玩家手牌
	SpriteCardManage *m_pBaseCard;              //底牌
    CCSprite *m_pFlyCards[8];			//发牌时，每个玩家每帧飞出两张牌

	GameLayer *m_pGameLayer;
};

#endif
