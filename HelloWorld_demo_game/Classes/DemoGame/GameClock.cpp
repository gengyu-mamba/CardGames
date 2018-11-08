#include "GameClock.h"

#include "PositionConfig.h"

#include "GameLayer.h"

GameClock::GameClock(GameLayer *pGameLayer)
{
	m_iTime = 0;

	m_pGameLayer = pGameLayer;

	m_pNumLable = NULL;
}

GameClock::~GameClock()
{
	
}

void GameClock::onEnter()
{
	CCLayer::onEnter();

	m_pSpriteBG = CCSprite::create("clock.png");
	addChild(m_pSpriteBG);
	
	m_pNumLable = CCLabelAtlas::create("123", "clocknum.png", 18, 28, '0');
	addChild(m_pNumLable);

	setVisible(false);	//Ĭ������
	
}

void GameClock::onExit()
{
	CCLayer::onExit();
	
}

void GameClock::ShowClock(int iTime,int iTablePos)
{
	setVisible(true);

	m_iTime = iTime;
	m_iTablePos = iTablePos;
	
	m_pSpriteBG->setPosition(g_ptClock[m_iTablePos]);
	
	m_pNumLable->setPosition(g_ptClock[m_iTablePos].x-10, g_ptClock[m_iTablePos].y-10);

	char str[2];	
	m_pNumLable->setString(itoa(m_iTime, str, 10));//����ͼƬ��ʾ��ǰ�Ķ�������

	schedule(schedule_selector(GameClock::OnSecondTimer),1.0f);	//��Ҫ��ʾ��ʱ��ſ�����ʱ��
}

void GameClock::ResetClock()
{
	m_iTime = 0;
	setVisible(false);	
	unscheduleAllSelectors();//ͣ����ʱ��
}

void GameClock::OnSecondTimer(float dt)
{
	if(m_iTime > 0)
	{
		m_iTime--;
		//m_pNumLable->setNum(m_iTime);
		char str[2];
		m_pNumLable->setString(itoa(m_iTime, str, 10));//����ͼƬ��ʾ��ǰ�Ķ�������
		if(m_iTime == 0)
		{
			setVisible(false);	//����ʱ��������
			unscheduleAllSelectors();//��ʾ�����ͣ����ʱ��
			
			m_pGameLayer->OnAutoSendCard(m_iTablePos);	//�Զ�����
			
		}
	}
}