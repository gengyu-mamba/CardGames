#include "OtherHandCard.h"

#include "PositionConfig.h"

OtherHandCard::OtherHandCard(int iTablePos)
{
	m_iTablePos = iTablePos;
}

OtherHandCard::~OtherHandCard()
{
	
}

void OtherHandCard::onEnter()
{
	SpriteCardManage::onEnter();

	CCSprite *pSprite = CCSprite::create("cardcountbox.png");
	pSprite->setPosition(g_ptLeftCardNum[m_iTablePos]);
	addChild(pSprite);

	m_pLableLeftNum = CCLabelAtlas::create("0123456789", "leftcardnum.png", 14, 18, '0');
	m_pLableLeftNum->setPosition(g_ptLeftCardNum[m_iTablePos].x-12,g_ptLeftCardNum[m_iTablePos].y-10);
	addChild(m_pLableLeftNum);
	setVisible(false);
}

void OtherHandCard::onExit()
{
	SpriteCardManage::onExit();
}

void OtherHandCard::ResetAllCardPosition()
{
	int i;
	int iBeginX = g_ptHandCard[m_iTablePos].x+25;
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		m_vcSpriteCard[i]->pSpriteCard->setScale(g_fOtherHandScale);

		m_vcSpriteCard[i]->iX = iBeginX+i*g_iOtherHandCardGap+g_sizeSingleCard.width/2*g_fOtherHandScale;
		m_vcSpriteCard[i]->iY = g_ptHandCard[m_iTablePos].y;

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
	}
	
	if(m_vcSpriteCard.size() == 0)
	{
		setVisible(false);
	}
	else
	{
		setVisible(true);
		char str[3];
		m_pLableLeftNum->setString(itoa(m_vcSpriteCard.size(), str, 10));//数字图片显示当前的动作索引
	}
}

int OtherHandCard::GetRandSendCard(int *iCardIndex)
{
	//随机合法的出牌张数
	int iSendNum = rand()%6+1;
	if(iSendNum > m_vcSpriteCard.size())
	{
		iSendNum = m_vcSpriteCard.size();
	}

	for(int i = 0;i<iSendNum;i++)
	{
		iCardIndex[i] = m_vcSpriteCard[i]->iCardIndex;
	}

	return iSendNum;
}