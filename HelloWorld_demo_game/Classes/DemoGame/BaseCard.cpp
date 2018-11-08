#include "BaseCard.h"

#include "PositionConfig.h"

BaseCard::BaseCard()
{
	
}

BaseCard::~BaseCard()
{
	
}

void BaseCard::ResetAllCardPosition()
{
	int i;
	int iTotalWidth = (m_vcSpriteCard.size()-1)*g_iBaseCardGap+g_sizeSingleCard.width*g_fBaseCardScale;
	int iBeginX = (g_iWindowWidth-iTotalWidth)/2;
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		m_vcSpriteCard[i]->pSpriteCard->setScale(g_fBaseCardScale);

		m_vcSpriteCard[i]->iX = iBeginX+i*g_iBaseCardGap+g_sizeSingleCard.width/2*g_fBaseCardScale;
		m_vcSpriteCard[i]->iY = g_ptDealCardIni.y;

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
	}
}
