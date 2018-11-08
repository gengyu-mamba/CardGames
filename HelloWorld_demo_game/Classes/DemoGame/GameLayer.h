#ifndef _GAME_LAYER_
#define _GAME_LAYER_

#include "cocos2d.h"
USING_NS_CC;

#include "DemoPlayerAct\PlayerHead.h"
#include "PositionConfig.h"
#include "BaseCard.h"
#include "DealCard.h"
#include "GameClock.h"
#include "OtherHandCard.h"
#include "SelfHandCard.h"
#include "SendCard.h"

#include <vector>
using namespace std;

class GameLayer : public CCLayer 
{
    
public:
    GameLayer();
    virtual ~GameLayer();

	void OnDealCardOK();															//DealCard发完牌后调用

	void OnSendCard(int iSendCardIndex[],int iSendNum,int iTablePos);				//SelfHandCard里点击出牌按钮后调用，其他玩家出牌也会调用

	void OnAutoSendCard(int iTablePos);												//GameClock时钟到了调用
private:
    virtual void onEnter();
    virtual void onExit();
	
    vector<int> m_vcAllCardIndex;			//存放所有牌的vector

    PlayerHead *m_pPlayerHead[4];			//四个玩家头像

	DealCard *m_pDealCard;					//发牌对象
	SpriteCardManage *m_pHandCard[4];		//四个玩家手牌
    BaseCard *m_pBaseCard;					//底牌
    SendCard *m_pSendCard[4];				//出牌

	GameClock *m_pGameClock;				//时钟
};

#endif

