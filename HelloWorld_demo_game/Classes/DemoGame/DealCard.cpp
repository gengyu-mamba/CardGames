#include "DealCard.h"
#include "PositionConfig.h"

#include "GameLayer.h"

DealCard::DealCard(GameLayer *pGameLayer,vector<int> vcAllCard,SpriteCardManage **pHandCard,SpriteCardManage *pBaseCard)   
{
	for(int i=0;i<vcAllCard.size();i++) 
    {
		m_vcAllCard.push_back(vcAllCard[i]);
    }  
	m_pHandCard = pHandCard;
	m_pBaseCard = pBaseCard;
    
	m_pGameLayer = pGameLayer;
}

DealCard::~DealCard()
{
	
}

void DealCard::onEnter()
{
    SpriteCardManage::onEnter();

    int i;
    for (i= 0;i<8;i++) 
	{
        m_pFlyCards[i] = CCSprite::create("flycard.png");
        m_pFlyCards[i]->setScale(0.65f);
        addChild(m_pFlyCards[i]);
        m_pFlyCards[i]->setVisible(false);
    }

    scheduleUpdate();
}

void DealCard::onExit()
{
    SpriteCardManage::onExit();
    

}


void DealCard::ResetAllCardPosition()
{
	int i;
	int iTotalWidth = (m_vcSpriteCard.size()-1)*g_iDealCardIniGap+g_sizeSingleCard.width*g_fDealCardIniScale;
	int iBeginX = (g_iWindowWidth-iTotalWidth)/2;
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		m_vcSpriteCard[i]->pSpriteCard->setScale(g_fDealCardIniScale);

		m_vcSpriteCard[i]->iX = iBeginX+i*g_iDealCardIniGap+g_sizeSingleCard.width/2*g_fDealCardIniScale;
		m_vcSpriteCard[i]->iY = g_ptDealCardIni.y;

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
	}
}

const int dir_fly[4][2] = {1,0  ,-1,0,   0,1,    0,-1};	//飞行的方向变量
const int FLY_STEP_SPEED = 90;							//飞行速度

void DealCard::update(float dt)
{
	static unsigned int tmLast = 0;
	static bool bIsFlyCard = false;
	static int iDealCount = 0;
	static int iStep = 0;

	int i;
    cc_timeval now; 
	CCTime::gettimeofdayCocos2d(&now,NULL);
    unsigned int tmNow = now.tv_sec*1000+now.tv_usec/1000;
    
	int iTmGap;
	if(iStep == 0)
	{
		iTmGap = 20;
	}
	else
	{
		iTmGap = 60;
	}
    
    //发牌效果（发牌第二步执行）
    if(iStep == 1)
    {
        static int iFlyStep1 = 45;
        static int iFlyStep2 = 0;
        
        for(int i=0; i<4; i++) 
		{
            m_pFlyCards[i]->setVisible(true);
            m_pFlyCards[i]->setPosition(ccp(g_iWindowWidth/2+iFlyStep1*dir_fly[i][0],g_ptDealCardIni.y+iFlyStep1*dir_fly[i][1]));
                
            m_pFlyCards[i+4]->setVisible(true);
            m_pFlyCards[i+4]->setPosition(ccp(g_iWindowWidth/2+iFlyStep2*dir_fly[i][0],g_ptDealCardIni.y+iFlyStep2*dir_fly[i][1]));
        }
        
        iFlyStep1 += FLY_STEP_SPEED;
        if (iFlyStep1 >= 360) 
		{
            iFlyStep1 = 0;
        }
        iFlyStep2 += FLY_STEP_SPEED;
        if (iFlyStep2 >= 360) 
		{
            iFlyStep2 = 0;
        }
    }
    
    //发牌
	if(tmNow-tmLast >= iTmGap)
	{
		tmLast = tmNow;
		if(iStep == 0)					//第一步先初始化108张牌
		{
			this->AddCard(0,true);
			iDealCount++;
			if(iDealCount == 108)
			{
				iStep = 1;
				iDealCount = 0;
			}
		}
		else if(iStep == 1)				//第二步给4个玩家各发25张
		{
			for(i = 0;i<4;i++)
			{
				int iRand = rand()%m_vcAllCard.size();
				if(i == 1)
					m_pHandCard[i]->AddCard(m_vcAllCard[iRand]);	//给张随机牌
				else
					m_pHandCard[i]->AddCard(m_vcAllCard[iRand],true);	//给张随机牌，其他玩家牌背显示
				m_vcAllCard.erase(m_vcAllCard.begin()+iRand);	//发过后就移除

                RemoveCard(0);	
			}
			iDealCount++;
            
			if(iDealCount == 25)
			{
				iStep = 2;
				iDealCount = 0;
                int i;
                for (i=0;i<8;i++) 
				{
                    m_pFlyCards[i]->setVisible(false);
                }
			}
		}
		else if(iStep == 2)			//第三步剩余8张给底牌
		{
            m_pBaseCard->AddCard(m_vcAllCard[iDealCount],true);//底牌牌背显示
			iDealCount++;
			if(iDealCount == 8)
			{
				//静态变量就是全局变量，所以这里得重置，不然就算delete了再new出来，仍旧还是原值
				iDealCount = 0;
				iStep  = 0;
				tmLast = 0;
				m_pGameLayer->OnDealCardOK();
                return;
			}
		}
	}
	
}


