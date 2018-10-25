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

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);		//触摸（鼠标）按下事件，多点触摸
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);		//触摸（鼠标）拖拽事件，多点触摸
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);		//触摸（鼠标）弹起事件，多点触摸

	
	CCLabelTTF *m_pLableTouchInfo;		//显示触摸信息，文本字符串的显示对象

	CCLabelAtlas *m_pLableNum;			//图片数字显示对象

	CCMenuItemImage *m_pBtnTest;		//测试按钮

	void OnBtnTest(CCObject *pBtn);		//按钮响应函数

	CCSprite *m_pSpriteHeadAni;			//可动的人物头像
};

#endif