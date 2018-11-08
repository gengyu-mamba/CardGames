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

	setVisible(false);	//默认隐藏
	
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
	m_pNumLable->setString(itoa(m_iTime, str, 10));//数字图片显示当前的动作索引

	schedule(schedule_selector(GameClock::OnSecondTimer),1.0f);	//需要显示的时候才开启定时器
}

void GameClock::ResetClock()
{
	m_iTime = 0;
	setVisible(false);	
	unscheduleAllSelectors();//停掉定时器
}

void GameClock::OnSecondTimer(float dt)
{
	if(m_iTime > 0)
	{
		m_iTime--;
		//m_pNumLable->setNum(m_iTime);
		char str[2];
		m_pNumLable->setString(itoa(m_iTime, str, 10));//数字图片显示当前的动作索引
		if(m_iTime == 0)
		{
			setVisible(false);	//倒计时到了隐藏
			unscheduleAllSelectors();//显示完毕了停掉定时器
			
			m_pGameLayer->OnAutoSendCard(m_iTablePos);	//自动出牌
			
		}
	}
}