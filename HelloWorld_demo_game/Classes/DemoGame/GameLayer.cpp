#include "GameLayer.h"

#include "DemoCard\SpriteCardManage.h"

const int g_iClockTime = 3;

GameLayer::GameLayer()
{
	//初始化所有牌
    int i,j;
    for(j = 0;j<2;j++)
    {
        for(i = 0;i<60;i++)
        {
            if(i == 28 || i == 29 || i == 43 || i == 44 || i == 58 || i == 59)
            {
                continue;
            }
            m_vcAllCardIndex.push_back(i);
        }
    }

	srand(time(NULL));
    
}

GameLayer::~GameLayer()
{
    
}


void GameLayer::onEnter()
{
    CCLayer::onEnter();
    
	//背景图
	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");
	pSpriteBG->setPosition(ccp(g_iWindowWidth/2,g_iWindowHeight/2));	
	addChild(pSpriteBG);
    
	for(int i = 0;i<4;i++)
	{
		 //人物头像
		m_pPlayerHead[i] = new PlayerHead();
		m_pPlayerHead[i]->setPosition(g_ptPlayerHead[i]);
		addChild(m_pPlayerHead[i]);

		//出牌
		m_pSendCard[i] = new SendCard(i);
		addChild(m_pSendCard[i]);

		if(i == 1)
		{
			m_pHandCard[1] = new SelfHandCard(this);   //自己手牌
			m_pHandCard[1]->SetNeedShadow(true);
		}
		else
		{
			m_pHandCard[i] = new OtherHandCard(i);
		}
		addChild(m_pHandCard[i]);
	}
    
    //底牌
    m_pBaseCard=new BaseCard();
    addChild(m_pBaseCard);
    
    //计时器
    m_pGameClock=new GameClock(this);
    addChild(m_pGameClock);    

    //DealCard
    m_pDealCard = new DealCard(this,m_vcAllCardIndex,(SpriteCardManage**)m_pHandCard,(SpriteCardManage*)m_pBaseCard);
    addChild(m_pDealCard);
}

void GameLayer::onExit()
{
    CCLayer::onExit();
       
	//for(int i = 0;i<4;i++)
	//{
	//	CC_SAFE_DELETE(m_pPlayerHead[i]);
	//	CC_SAFE_DELETE(m_pHandCard[i]);
	//	CC_SAFE_DELETE(m_pSendCard[i]);
	//}
	
	//CC_SAFE_DELETE(m_pDealCard);
 //   CC_SAFE_DELETE(m_pBaseCard);
 //   CC_SAFE_DELETE(m_pGameClock);
   
}


void GameLayer::OnAutoSendCard(int iTablePos)
{
	int iSendCardIndex[25];
	int iSendNum = 0;
	if(iTablePos == 1)
	{
		iSendNum = ((SelfHandCard*)m_pHandCard[iTablePos])->GetRandSendCard(iSendCardIndex);
		((SelfHandCard*)m_pHandCard[1])->ShowSendBtn(false);	//自己自动出牌了也隐藏按钮
	}
	else
	{
		iSendNum = ((OtherHandCard*)m_pHandCard[iTablePos])->GetRandSendCard(iSendCardIndex);
	}
	OnSendCard(iSendCardIndex,iSendNum,iTablePos);	//出牌
}


void GameLayer::OnDealCardOK()
{
	m_pHandCard[1]->setTouchEnabled(true);	//允许触摸
    m_pGameClock->ShowClock(g_iClockTime,0);	//0位置（左方）玩家最先开始出牌计时

	removeChild(m_pDealCard,true);				//移除发牌
}


void GameLayer::OnSendCard(int iSendCardIndex[],int iSendNum,int iTablePos)
{
	m_pGameClock->ResetClock();			//停掉计时器

	m_pSendCard[iTablePos]->RemoveAllCard();

	int i;
	for(i = 0;i<iSendNum;i++)
	{
		m_pHandCard[iTablePos]->RemoveCard(iSendCardIndex[i]);

		m_pSendCard[iTablePos]->AddCard(iSendCardIndex[i]);
	}

	if(m_pHandCard[iTablePos]->GetCardCount() == 0)//出完牌的玩家永久放胜利动画
	{
		m_pPlayerHead[iTablePos]->ShowPlayerAct(HAPPY_ACT,-1);
	}

	//找下个有牌的玩家出牌
	int iNextPos = iTablePos;
	while(1)
	{
		iNextPos++;
		if(iNextPos == 4)
			iNextPos = 0;

		if(m_pHandCard[iNextPos]->GetCardCount() > 0)
			break;

		if(iNextPos == iTablePos)	//所有人都没牌了，游戏结束，显示底牌
		{
			m_pBaseCard->ShowBackAllCard(false);
			return;
		}
	}
	
	m_pGameClock->ShowClock(g_iClockTime,iNextPos);	//下方玩家开始出牌计时

	if(iNextPos == 1)	//是自己的话，显示按钮
	{
		((SelfHandCard*)m_pHandCard[iNextPos])->ShowSendBtn(true);
	}

}