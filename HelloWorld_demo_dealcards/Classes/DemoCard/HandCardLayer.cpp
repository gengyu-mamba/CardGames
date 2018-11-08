#include "HandCardLayer.h"

#include "DealCardLayer.h"

HandCardLayer::HandCardLayer(DealCardLayer *pDealCardLayer)
{
	m_iTouchesBeganCardIndex = -1;
	m_pDealCardLayer = pDealCardLayer;
}


HandCardLayer::~HandCardLayer()
{
}

void HandCardLayer::onEnter()
{
	SpriteCardManage::onEnter();

	m_iTouchesBeganCardIndex = -1;

	//���ư�ť
	m_pBtnSend = CCMenuItemImage::create("score-1-1.png", "score-1-2.png", "score-1-3.png", this, menu_selector(HandCardLayer::OnBtnSend));
	m_pBtnSend->setPosition(ccp(1016 / 2, 703 / 2));
	m_pBtnSend->setEnabled(false);

	CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(m_pBtnSend);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
}

void HandCardLayer::onExit()
{
	SpriteCardManage::onExit();

	m_iTouchesBeganCardIndex = -1;
}

void HandCardLayer::ResetAllCardPosition()
{
	int i;
	int iTotalWidth = (m_vcSpriteCard.size() - 1) * 40 + 141;
	int iBeginX = (1016 - iTotalWidth) / 2;
	for (i = 0; i < m_vcSpriteCard.size(); ++i)
	{
		m_vcSpriteCard[i]->iX = iBeginX + i * 40 + 70;
		m_vcSpriteCard[i]->iY = 120;
		if (m_vcSpriteCard[i]->bSelected)
		{
			m_vcSpriteCard[i]->iY += 30;
		}
		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
		m_vcSpriteCard[i]->pSpriteShadow->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
	}

	//����������λ�õ�ʱ��Ҫȡ��������ԭʼ����Ϣ�����ǵ����������ѡ�Ʋ�����ʱ���ⲿ������AddCard����RemoveCard�������ԭʼ����Ϣ����
	if (m_iTouchesBeganCardIndex != -1)
	{
		m_vcSpriteCard[m_iTouchesBeganCardIndex]->bShadow = false;
		m_vcSpriteCard[m_iTouchesBeganCardIndex]->pSpriteShadow->setVisible(false);
		m_iTouchesBeganCardIndex = -1;
	}
}

void HandCardLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();	//pTouches�Ǹ��������������˶�㴥����Ϣ�������������ֻ������
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	//�жϿ�ʼ�������������ϣ������ƣ����Ϸ����ƣ���Ҫ���ȱ��ж�ѡ��
	m_iTouchesBeganCardIndex = -1;
	int i;
	for (i = m_vcSpriteCard.size() - 1; i >= 0; i--)
	{
		if (m_vcSpriteCard[i]->pSpriteCard->boundingBox().containsPoint(ptLogic))
		{
			m_iTouchesBeganCardIndex = i;
			m_vcSpriteCard[m_iTouchesBeganCardIndex]->bShadow = true;
			m_vcSpriteCard[m_iTouchesBeganCardIndex]->pSpriteShadow->setVisible(true);
			break;
		}
	}
}

void HandCardLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();	//pTouches�Ǹ��������������˶�㴥����Ϣ�������������ֻ������
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	if (m_iTouchesBeganCardIndex != -1)
	{
		int iMoveCardIndex = -1;
		int i;
		for (i = m_vcSpriteCard.size() - 1; i >= 0; i--)
		{
			if (m_vcSpriteCard[i]->pSpriteCard->boundingBox().containsPoint(ptLogic))
			{
				iMoveCardIndex = i;
				break;
			}
		}

		if (iMoveCardIndex != -1)	//�������ϣ�����iMoveCardIndex��m_iTouchesBeganCardIndex֮������ʾ��Ӱ
		{
			//��ȡ��������Ӱ
			for (i = 0; i < m_vcSpriteCard.size(); ++i)
			{
				m_vcSpriteCard[i]->bShadow = false;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(false);
			}

			int iMinIndex, iMaxIndex;
			if (iMoveCardIndex >= m_iTouchesBeganCardIndex)
			{
				iMaxIndex = iMoveCardIndex;
				iMinIndex = m_iTouchesBeganCardIndex;
			} 
			else
			{
				iMaxIndex = m_iTouchesBeganCardIndex;
				iMinIndex = iMoveCardIndex;
			}
			for (i = iMinIndex; i <= iMaxIndex; ++i)
			{
				m_vcSpriteCard[i]->bShadow = true;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(true);
			}
		}
	}
}

void HandCardLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();	//pTouches�Ǹ��������������˶�㴥����Ϣ�������������ֻ������
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	int i;
	if (m_iTouchesBeganCardIndex == -1)
	{
		for (i = 0; i < m_vcSpriteCard.size(); ++i)
		{
			m_vcSpriteCard[i]->bSelected = false;
		}
		ResetAllCardPosition();
		m_pBtnSend->setEnabled(false);
	} 
	else if (m_iTouchesBeganCardIndex != -1)
	{
		//��������Ӱ����Ϊ��select״̬������ȡ����Ӱ״̬
		for (i = 0; i < m_vcSpriteCard.size(); i++)
		{
			if (m_vcSpriteCard[i]->bShadow == true)
			{
				m_vcSpriteCard[i]->bSelected = !m_vcSpriteCard[i]->bSelected;
				m_vcSpriteCard[i]->bShadow = false;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(false);
			}
		}

		m_iTouchesBeganCardIndex = -1;

		ResetAllCardPosition();
		//ѡ�л����ó��ư�ť
		m_pBtnSend->setEnabled(false);
		for (i = 0; i < m_vcSpriteCard.size(); i++)
		{
			if (m_vcSpriteCard[i]->bSelected == true)
			{
				m_pBtnSend->setEnabled(true);
				break;
			}
		}
	}
}

void HandCardLayer::OnBtnSend(CCObject *pBtn)
{
	m_pBtnSend->setEnabled(false);
	int i;
	int iSelectCardIndex[20];
	int iSelectCardNum = 0;
	for (i = 0; i < m_vcSpriteCard.size(); i++)
	{
		if (m_vcSpriteCard[i]->bSelected == true)
		{
			iSelectCardIndex[iSelectCardNum] = m_vcSpriteCard[i]->iCardIndex;
			iSelectCardNum++;
		}
	}
	m_pDealCardLayer->OnSelfSendCard(iSelectCardIndex, iSelectCardNum);
}

