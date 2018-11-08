#include "DealCardLayer.h"

DealCardLayer::DealCardLayer()
{
	int i;
	for (i = 0; i < 60; i++)
	{
		if (i == 28 || i == 29 || i == 43 || i == 44 || i == 58 || i == 59)
		{
			continue;
		}
		m_vcAllCardIndex.push_back(i);
	}

	srand(time(NULL));
}


DealCardLayer::~DealCardLayer()
{
}

void DealCardLayer::onEnter()
{
	CCLayer::onEnter();

	schedule(schedule_selector(DealCardLayer::OnDealCardTimer), 0.15f);

	//背景图
	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");
	pSpriteBG->setPosition(ccp(1016 / 2, 703 / 2));
	addChild(pSpriteBG);

	//出牌Layer
	m_pSendCardLayer = new SendCardLayer();
	addChild(m_pSendCardLayer);

	//手中牌Layer
	m_pHandCardLayer = new HandCardLayer(this);
	m_pHandCardLayer->SetNeedShadow(true);//手中牌需要操作阴影
	addChild(m_pHandCardLayer);
}

void DealCardLayer::onExit()
{
	CCLayer::onExit();

	//CC_SAFE_DELETE(m_pSendCardLayer);
	//CC_SAFE_DELETE(m_pHandCardLayer);
}

void DealCardLayer::OnDealCardTimer(float dt)
{
	if (m_pHandCardLayer->GetCardCount() == 17)
	{
		this->unscheduleAllSelectors();
		m_pHandCardLayer->setTouchEnabled(true);
		return;
	}

	int iRand = rand() % m_vcAllCardIndex.size();
	m_pHandCardLayer->AddCard(m_vcAllCardIndex[iRand]);
	m_vcAllCardIndex.erase(m_vcAllCardIndex.begin() + iRand);
}

void DealCardLayer::OnSelfSendCard(int iSendCardIndex[], int iSendNum)
{
	m_pSendCardLayer->RemoveAllCard();
	int i;
	for (i = 0; i < iSendNum; i++)
	{
		m_pHandCardLayer->RemoveCard(iSendCardIndex[i]);

		m_pSendCardLayer->AddCard(iSendCardIndex[i]);
	}
}
