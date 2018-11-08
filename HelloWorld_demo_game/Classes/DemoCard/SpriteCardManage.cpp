#include "SpriteCardManage.h"


SpriteCardManage::SpriteCardManage()
{
	m_bNeedShadow = false;
}


SpriteCardManage::~SpriteCardManage()
{
}

void SpriteCardManage::onEnter()
{
	CCLayer::onEnter();
	CCSpriteFrameCache *pSfcCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pSfcCache->addSpriteFramesWithFile("CardLayer1.plist");
	pSfcCache->addSpriteFramesWithFile("CardLayer2.plist");
}

void SpriteCardManage::onExit()
{
	CCLayer::onExit();
}

SpriteCardDef* SpriteCardManage::AddCard(int iCardIndex, bool bBack /*= false*/, bool bSelected /*= false*/, bool bReorder /*= true*/)
{
	SpriteCardDef *pCard = new SpriteCardDef();
	memset(pCard, 0, sizeof(SpriteCardDef));
	pCard->fScale = 1.0f;
	pCard->iCardIndex = iCardIndex;
	pCard->iZ = 100 + m_vcSpriteCard.size();
	pCard->bBack = bBack;
	pCard->bSelected = bSelected;

	char path[32];
	if (bBack == true)
	{
		strcpy(path, "cardback.png");
	}
	else
	{
		sprintf(path, "card%d.png", iCardIndex);
	}
	pCard->pSpriteCard = CCSprite::createWithSpriteFrameName(path);
	addChild(pCard->pSpriteCard, pCard->iZ);
	if (m_bNeedShadow)
	{
		pCard->pSpriteShadow = CCSprite::createWithSpriteFrameName("p_shadow.png");
		pCard->pSpriteShadow->setVisible(false);
		addChild(pCard->pSpriteShadow, pCard->iZ);
	}
	m_vcSpriteCard.push_back(pCard);

	if (bReorder == true)
	{
		ReorderCard();
	}
	else
	{
		ResetAllCardPosition();
	}
	return pCard;
}

void SpriteCardManage::ReorderCard()
{
	int i, a, b;
	if (m_vcSpriteCard.size() > 1)
	{
		for (a = 0; a < m_vcSpriteCard.size() - 1; ++a)
		{
			for (b = a + 1; b < m_vcSpriteCard.size(); ++b)
			{
				int iValA = CheckCardValue(m_vcSpriteCard[a]->iCardIndex);
				int iValB = CheckCardValue(m_vcSpriteCard[b]->iCardIndex);
				if (iValA < iValB)
				{
					SpriteCardDef* tmp = m_vcSpriteCard[a];
					m_vcSpriteCard[a] = m_vcSpriteCard[b];
					m_vcSpriteCard[b] = tmp;
				}
			}
		}
	}

	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		m_vcSpriteCard[i]->iZ = 100 + i;
	}

	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		reorderChild(m_vcSpriteCard[i]->pSpriteCard, m_vcSpriteCard[i]->iZ);
		if (m_vcSpriteCard[i]->pSpriteShadow)
		{
			reorderChild(m_vcSpriteCard[i]->pSpriteShadow, m_vcSpriteCard[i]->iZ);
		}
	}
	ResetAllCardPosition();
}

void SpriteCardManage::ResetAllSelectCard()
{
	for (int i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		m_vcSpriteCard[i]->bSelected = false;
	}
	ResetAllCardPosition();
}

void SpriteCardManage::ShowBackSingleCard(SpriteCardDef *pCard, bool bBack)
{
	pCard->bBack = bBack;
	char path[32];
	if (bBack == true)
	{
		strcpy(path, "cardback.png");
	}
	else
	{
		sprintf(path, "card%d.png", pCard->iCardIndex);
	}
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(path);
	pCard->pSpriteCard->setDisplayFrame(pFrame);
}

void SpriteCardManage::ShowBackAllCard(bool bBack)
{
	int i;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		ShowBackSingleCard(m_vcSpriteCard[i], bBack);
	}
}

void SpriteCardManage::RemoveCard(int iCardIndex, bool bReorder /*= true*/)
{
	int i;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		if (m_vcSpriteCard[i]->iCardIndex == iCardIndex)
		{
			SpriteCardDef *pCard = m_vcSpriteCard[i];
			removeChild(pCard->pSpriteCard, true);
			if (m_bNeedShadow)
			{
				removeChild(pCard->pSpriteShadow, true);
			}
			m_vcSpriteCard.erase(m_vcSpriteCard.begin() + i);
			delete pCard;
			break;
		}
	}

	if (bReorder == true)
	{
		ReorderCard();
	}
	else
	{
		ResetAllCardPosition();
	}
}

void SpriteCardManage::RemoveCard(SpriteCardDef *pCard, bool bReorder /*= true*/)
{
	int i;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		if (m_vcSpriteCard[i] == pCard)
		{
			SpriteCardDef *pCard = m_vcSpriteCard[i];
			removeChild(pCard->pSpriteCard, true);
			if (m_bNeedShadow)
			{
				removeChild(pCard->pSpriteShadow, true);
			}
			m_vcSpriteCard.erase(m_vcSpriteCard.begin() + i);
			delete pCard;
			break;
		}
	}

	if (bReorder == true)
	{
		ReorderCard();
	}
	else
	{
		ResetAllCardPosition();
	}
}

void SpriteCardManage::RemoveAllCard()
{
	int i;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		SpriteCardDef *pCard = m_vcSpriteCard[i];
		removeChild(pCard->pSpriteCard, true);
		if (pCard->pSpriteShadow)
		{
			removeChild(pCard->pSpriteShadow, true);
		}
		delete pCard;
	}
	m_vcSpriteCard.clear();

	ResetAllCardPosition();
}

int SpriteCardManage::CheckCardValue(int iCardNum)
{
	int iVal = -1;
	switch (iCardNum%15)
	{
	case 0:
		iVal = 14;		//A
		break;
	case 1:
		iVal = 15;		//2
		break;
	case 2:
		iVal = 3;		//3
		break;
	case 3:
		iVal = 4;		//4
		break;
	case 4:
		iVal = 5;		//5
		break;
	case 5:
		iVal = 6;		//6
		break;
	case 6:
		iVal = 7;		//7
		break;
	case 7:
		iVal = 8;		//8
		break;
	case 8:
		iVal = 9;		//9
		break;
	case 9:
		iVal = 10;		//10
		break;
	case 10:
		iVal = 11;		//J
		break;
	case 11:
		iVal = 12;		//Q
		break;
	case 12:
		iVal = 13;		//K
		break;
	case 13:
		iVal = 16;		//Joker(Ð¡)
		break;
	case 14:
		iVal = 17;		//Joker(´ó£©
		break;
	default:
		iVal = 0;
		break;
	}
	return iVal;
}
