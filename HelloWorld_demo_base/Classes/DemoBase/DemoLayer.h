#ifndef DEMO_LAYER_H
#define DEMO_LAYER_H

#include "cocos2d.h"
USING_NS_CC;

class DemoLayer : public cocos2d::CCLayer
{
public:
	DemoLayer();
	virtual ~DemoLayer();

private:
	virtual void onEnter();

	virtual void onExit();

	virtual void update(float dt);

	void OnSecondsTimer(float dt);

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);		//��������꣩�����¼�����㴥��
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);		//��������꣩��ק�¼�����㴥��
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);		//��������꣩�����¼�����㴥��

	
	CCLabelTTF *m_pLableTouchInfo;		//��ʾ������Ϣ���ı��ַ�������ʾ����

	CCLabelAtlas *m_pLableNum;			//ͼƬ������ʾ����

	CCMenuItemImage *m_pBtnTest;		//���԰�ť

	void OnBtnTest(CCObject *pBtn);		//��ť��Ӧ����

	CCSprite *m_pSpriteHeadAni;			//�ɶ�������ͷ��
};

#endif