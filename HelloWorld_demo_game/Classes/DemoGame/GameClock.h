#ifndef GAME_CLOCK_H
#define GAME_CLOCK_H

#include "cocos2d.h"
USING_NS_CC;


class GameLayer;
class GameClock :public CCLayer
{   
public:
    GameClock(GameLayer *pGameLayer);
    virtual ~GameClock();
	
	void ShowClock(int iTime,int iTablePos);

	void ResetClock();
private:
	virtual void onEnter();	
	virtual void onExit();

	void OnSecondTimer(float dt);

	CCSprite *m_pSpriteBG;

	CCLabelAtlas *m_pNumLable;

	int m_iTime;
	int m_iTablePos;
	
	GameLayer *m_pGameLayer;
};

#endif
