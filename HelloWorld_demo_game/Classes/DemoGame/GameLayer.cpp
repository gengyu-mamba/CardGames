#include "GameLayer.h"

#include "DemoCard\SpriteCardManage.h"

const int g_iClockTime = 3;

GameLayer::GameLayer()
{
	//��ʼ��������
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
    
	//����ͼ
	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");
	pSpriteBG->setPosition(ccp(g_iWindowWidth/2,g_iWindowHeight/2));	
	addChild(pSpriteBG);
    
	for(int i = 0;i<4;i++)
	{
		 //����ͷ��
		m_pPlayerHead[i] = new PlayerHead();
		m_pPlayerHead[i]->setPosition(g_ptPlayerHead[i]);
		addChild(m_pPlayerHead[i]);

		//����
		m_pSendCard[i] = new SendCard(i);
		addChild(m_pSendCard[i]);

		if(i == 1)
		{
			m_pHandCard[1] = new SelfHandCard(this);   //�Լ�����
			m_pHandCard[1]->SetNeedShadow(true);
		}
		else
		{
			m_pHandCard[i] = new OtherHandCard(i);
		}
		addChild(m_pHandCard[i]);
	}
    
    //����
    m_pBaseCard=new BaseCard();
    addChild(m_pBaseCard);
    
    //��ʱ��
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
		((SelfHandCard*)m_pHandCard[1])->ShowSendBtn(false);	//�Լ��Զ�������Ҳ���ذ�ť
	}
	else
	{
		iSendNum = ((OtherHandCard*)m_pHandCard[iTablePos])->GetRandSendCard(iSendCardIndex);
	}
	OnSendCard(iSendCardIndex,iSendNum,iTablePos);	//����
}


void GameLayer::OnDealCardOK()
{
	m_pHandCard[1]->setTouchEnabled(true);	//������
    m_pGameClock->ShowClock(g_iClockTime,0);	//0λ�ã��󷽣�������ȿ�ʼ���Ƽ�ʱ

	removeChild(m_pDealCard,true);				//�Ƴ�����
}


void GameLayer::OnSendCard(int iSendCardIndex[],int iSendNum,int iTablePos)
{
	m_pGameClock->ResetClock();			//ͣ����ʱ��

	m_pSendCard[iTablePos]->RemoveAllCard();

	int i;
	for(i = 0;i<iSendNum;i++)
	{
		m_pHandCard[iTablePos]->RemoveCard(iSendCardIndex[i]);

		m_pSendCard[iTablePos]->AddCard(iSendCardIndex[i]);
	}

	if(m_pHandCard[iTablePos]->GetCardCount() == 0)//�����Ƶ�������÷�ʤ������
	{
		m_pPlayerHead[iTablePos]->ShowPlayerAct(HAPPY_ACT,-1);
	}

	//���¸����Ƶ���ҳ���
	int iNextPos = iTablePos;
	while(1)
	{
		iNextPos++;
		if(iNextPos == 4)
			iNextPos = 0;

		if(m_pHandCard[iNextPos]->GetCardCount() > 0)
			break;

		if(iNextPos == iTablePos)	//�����˶�û���ˣ���Ϸ��������ʾ����
		{
			m_pBaseCard->ShowBackAllCard(false);
			return;
		}
	}
	
	m_pGameClock->ShowClock(g_iClockTime,iNextPos);	//�·���ҿ�ʼ���Ƽ�ʱ

	if(iNextPos == 1)	//���Լ��Ļ�����ʾ��ť
	{
		((SelfHandCard*)m_pHandCard[iNextPos])->ShowSendBtn(true);
	}

}