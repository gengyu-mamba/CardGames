#include "SendCard.h"

#include "PositionConfig.h"

SendCard::SendCard(int iTablePos)
{
	m_iTablePos = iTablePos;
}

SendCard::~SendCard()
{
	
}

void SendCard::ResetAllCardPosition()
{
	int i,iBeginX;
	if(m_iTablePos == 0)
	{
		iBeginX = g_ptSendCard[m_iTablePos].x;
	}
	else if(m_iTablePos == 1 || m_iTablePos == 3)
	{
		int iTotalWidth = (m_vcSpriteCard.size()-1)*g_iSendCardGap+g_sizeSingleCard.width*g_fSendCardScale;
		iBeginX = (g_iWindowWidth-iTotalWidth)/2;
	}
	else if(m_iTablePos == 2)
	{
		int iTotalWidth = (m_vcSpriteCard.size()-1)*g_iSendCardGap+g_sizeSingleCard.width*g_fSendCardScale;
		iBeginX = g_ptSendCard[m_iTablePos].x-iTotalWidth;
	}
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		m_vcSpriteCard[i]->pSpriteCard->setScale(g_fSendCardScale);

		m_vcSpriteCard[i]->iX = iBeginX+i*g_iSendCardGap+g_sizeSingleCard.width/2*g_fSendCardScale;
		m_vcSpriteCard[i]->iY = g_ptSendCard[m_iTablePos].y;

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX,m_vcSpriteCard[i]->iY));
	}
	
}