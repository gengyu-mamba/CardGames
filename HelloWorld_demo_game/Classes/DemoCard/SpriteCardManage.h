#ifndef __SPRITE_CARD_MANAGE_H__
#define __SPRITE_CARD_MANAGE_H__

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

typedef struct SpriteCard
{
	int iCardIndex;
	int iX;
	int iY;
	int iZ;
	float fScale;
	float fAngle;
	bool bSelected;
	bool bShadow;
	bool bBack;
	CCSprite *pSpriteCard;
	CCSprite *pSpriteShadow;
}SpriteCardDef;

class SpriteCardManage : public CCLayer
{
public:
	SpriteCardManage();

	virtual ~SpriteCardManage();

	SpriteCardDef* AddCard(int iCardIndex, bool bBack = false, bool bSelected = false, bool bReorder = true);	//�����

	void ReorderCard();		//�ɴ�С����

	int GetCardCount(){ return m_vcSpriteCard.size(); }	//��ȡ������Ŀ

	void ResetAllSelectCard();	//��������ѡ����

	void ShowBackSingleCard(SpriteCardDef *pCard, bool bBack);	//���õ����Ƶ��Ʊ����ԣ����Ҫ��ԭ��û��ֵ���Ʊ���ֵ����������ʾ�Ļ��������ⲿ����Ҫ�ı�pCard->iCardIndex

	void ShowBackAllCard(bool bBack);	//�������е��Ƶ��Ʊ�����

	void RemoveCard(int iCardIndex, bool bReorder = true);	//ɾ����
	
	void RemoveCard(SpriteCardDef *pCard, bool bReorder = true);	//ͨ��ָ��ɾ����
	
	void RemoveAllCard();	//ɾ��������

	void SetNeedShadow(bool bNeed){ m_bNeedShadow = bNeed; }		//������Ҫ������Ӱ

protected:
	virtual void onEnter();

	virtual void onExit();

	vector<SpriteCardDef*> m_vcSpriteCard;

	bool m_bNeedShadow;

	static int CheckCardValue(int iCardNum);

	virtual void ResetAllCardPosition(){};						//������λ�ã���Ҫʵ������ʵ��
};

#endif

