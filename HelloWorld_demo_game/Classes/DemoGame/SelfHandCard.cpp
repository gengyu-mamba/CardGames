#include "SelfHandCard.h"

#include "GameLayer.h"

SelfHandCard::SelfHandCard(GameLayer *pGameLayer)
{
	m_iTouchesBeganCardIndex = -1;

	m_pGameLayer = pGameLayer;
}

SelfHandCard::~SelfHandCard()
{
	
}


void SelfHandCard::onEnter()
{
	SpriteCardManage::onEnter();
	
	m_iTouchesBeganCardIndex = -1;

	//出牌按钮
	m_pBtnSend = CCMenuItemImage::create("score-1-1.png", "score-1-2.png", "score-1-3.png", this, menu_selector(SelfHandCard::OnBtnSend));
	m_pBtnSend->setPosition(g_ptBtnSend);
	m_pBtnSend->setEnabled(false);
	m_pBtnSend->setVisible(false);

	CCMenu* pMenu = CCMenu::create(m_pBtnSend, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
}

void SelfHandCard::onExit()
{
	SpriteCardManage::onExit();
	
	m_iTouchesBeganCardIndex = -1;
}

void SelfHandCard::ResetAllCardPosition()
{
	int i;
	
	int iTotalWidth = (m_vcSpriteCard.size()-1)*g_iSelfHandCardGap+g_sizeSingleCard.width*g_fSelfHandScale;
	int iBeginX = (g_iWindowWidth-iTotalWidth)/2;
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		m_vcSpriteCard[i]->iX = iBeginX+i*g_iSelfHandCardGap+g_sizeSingleCard.width*g_fSelfHandScale/2;
		m_vcSpriteCard[i]->iY = g_ptHandCard[1].y;
		if(m_vcSpriteCard[i]->bSelected)
		{
			m_vcSpriteCard[i]->iY += g_iHandCardSelectY;
		}
		m_vcSpriteCard[i]->pSpriteCard->setScale(g_fSelfHandScale);
		m_vcSpriteCard[i]->pSpriteShadow->setScale(g_fSelfHandScale);

		m_vcSpriteCard[i]->pSpriteCard->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));
		m_vcSpriteCard[i]->pSpriteShadow->setPosition(ccp(m_vcSpriteCard[i]->iX, m_vcSpriteCard[i]->iY));

		m_vcSpriteCard[i]->pSpriteShadow->setVisible(false);	//重置牌位置需要取消阴影状态
	}

	//重新设置牌位置的时候要取消掉触摸原始点信息，考虑到玩家在做拖选牌操作的时候，外部调用了AddCard或者RemoveCard导致这个原始点信息出错
	if(m_iTouchesBeganCardIndex != -1)
	{
		m_vcSpriteCard[m_iTouchesBeganCardIndex]->bShadow = false;
		m_vcSpriteCard[m_iTouchesBeganCardIndex]->pSpriteShadow->setVisible(false);
		m_iTouchesBeganCardIndex = -1;	
	}

}

void SelfHandCard::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息，我们这个需求只处理单点	
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	//判断开始点是在哪张牌上，靠右牌(叠上方的牌)需要优先被判断选中
	m_iTouchesBeganCardIndex = -1;
	int i;
	for(i = m_vcSpriteCard.size()-1;i>=0;i--)
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

void SelfHandCard::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息，我们这个需求只处理单点	
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	if(m_iTouchesBeganCardIndex != -1)
	{
		int iMoveCardIndex = -1;
		int i;
		for(i = m_vcSpriteCard.size()-1;i>=0;i--)
		{
			if (m_vcSpriteCard[i]->pSpriteCard->boundingBox().containsPoint(ptLogic))
			{
				iMoveCardIndex = i;
				break;
			}
		}

		
		if(iMoveCardIndex != -1)	//在牌面上，设置iMoveCardIndex和m_iTouchesBeganCardIndex之间牌显示阴影
		{
			//先取消所有阴影
			for(i = 0;i<m_vcSpriteCard.size();i++)
			{
				m_vcSpriteCard[i]->bShadow = false;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(false);
			}


			int iMinIndex,iMaxIndex;
			if(iMoveCardIndex >= m_iTouchesBeganCardIndex)
			{
				iMaxIndex = iMoveCardIndex;
				iMinIndex = m_iTouchesBeganCardIndex;
			}
			else
			{
				iMaxIndex = m_iTouchesBeganCardIndex;
				iMinIndex = iMoveCardIndex;
			}
			for(i = iMinIndex;i<= iMaxIndex;i++)
			{
				m_vcSpriteCard[i]->bShadow = true;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(true);
			}

		}
	}
}

void SelfHandCard::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息，我们这个需求只处理单点	
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	int i;
	if(m_iTouchesBeganCardIndex == -1)	//没有选中过牌的点击，取消所有选择
	{
		for(i = 0;i<m_vcSpriteCard.size();i++)
		{
			m_vcSpriteCard[i]->bSelected = false;
		}
		ResetAllCardPosition();
		m_pBtnSend->setEnabled(false);
	}
	else if(m_iTouchesBeganCardIndex != -1)
	{
		
		//设置有阴影的牌为反select状态，并且取消阴影状态		
		for(i = 0;i<m_vcSpriteCard.size();i++)
		{
			if(m_vcSpriteCard[i]->bShadow == true)
			{
				m_vcSpriteCard[i]->bSelected = !m_vcSpriteCard[i]->bSelected;

				m_vcSpriteCard[i]->bShadow = false;
				m_vcSpriteCard[i]->pSpriteShadow->setVisible(false);
			}
		}

		m_iTouchesBeganCardIndex = -1;
		
		ResetAllCardPosition();

		if(m_pBtnSend->isVisible() == true)
		{
			//选中话可用出牌按钮
			m_pBtnSend->setEnabled(false);
			for(i = 0;i<m_vcSpriteCard.size();i++)
			{
				if(m_vcSpriteCard[i]->bSelected == true)
				{
					m_pBtnSend->setEnabled(true);
					break;
				}
			}
		}
	}
	
}

void SelfHandCard::OnBtnSend(CCObject *pBtn)
{
	m_pBtnSend->setVisible(false);
	m_pBtnSend->setEnabled(false);

	int i;
	int iSelectCardIndex[20];
	int iSelectCardNum = 0;
	for(i = 0;i<m_vcSpriteCard.size();i++)
	{
		if(m_vcSpriteCard[i]->bSelected == true)
		{
			iSelectCardIndex[iSelectCardNum] = m_vcSpriteCard[i]->iCardIndex;
			iSelectCardNum++;
		}
	}

	m_pGameLayer->OnSendCard(iSelectCardIndex,iSelectCardNum,1);


}

int SelfHandCard::GetRandSendCard(int *iCardIndex)
{
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

void SelfHandCard::ShowSendBtn(bool bShow)
{
	m_pBtnSend->setVisible(bShow);
}