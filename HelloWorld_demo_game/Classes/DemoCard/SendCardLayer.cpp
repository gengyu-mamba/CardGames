#include "SendCardLayer.h"


SendCardLayer::SendCardLayer()
{
}


SendCardLayer::~SendCardLayer()
{
}

void SendCardLayer::ResetAllCardPosition()
{
	int i;

	int iTotalWidth = (m_vcSpriteCard.size() - 1) * 40 + 141;
	int iBeginX = (1016 - iTotalWidth) / 2;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		m_vcSpriteCard[i]->iX = iBeginX + i * 40 + 70;
		m_vcSpriteCard[i]->iY = 500;

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
	}
}
