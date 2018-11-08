#ifndef PLAYER_ACT_LAYER_H
#define PLAYER_ACT_LAYER_H

#include "cocos2d.h"
#include "PlayerHead.h"
USING_NS_CC;

class PlayerActLayer : public cocos2d::CCLayer
{
public:
	PlayerActLayer();

	virtual ~PlayerActLayer();

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float dt);

private:
	CCMenuItemSprite *m_pBtnHappy;	//高兴动作按钮

	CCMenuItemSprite *m_pBtnSad;		//惊讶动作按钮

	CCMenuItemImage *m_pBtnChangePlayer;	//更换人物按钮

	PlayerHead* m_pPlayerHead[4];

	void OnBtnHappy(CCObject *pBtn);

	void OnBtnSad(CCObject *pBtn);

	void OnBtnChangePlayer(CCObject *pBtn);
};

#endif

