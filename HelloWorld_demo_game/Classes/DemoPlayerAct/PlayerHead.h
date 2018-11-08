#ifndef PLAYER_Head_H
#define PLAYER_Head_H

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

enum PLAYER_ACT_TYPE
{
	NORMAL_ACT_1 = 0,
	NORMAL_ACT_2,
	NORMAL_ACT_3,
	SAD_ACT,
	HAPPY_ACT
};

class PlayerHead : public CCLayer
{
public:
	PlayerHead();

	virtual ~PlayerHead();

	static int GetUniqueImageIndex();	//获取随机唯一的头像

	void InitImage(int iImageIndex = -1); //初始化人物形象，默认值-1表示需要随机唯一，bCleanImage表示是否需要清理图像资源，当有可能同时两个PlayerHead对象使用同一图片的时候，这里为true就会有问题

	int GetImageIndex(){ return m_iImageIndex; }	//获取人物动画索引

	void RemoveImage();	//移除人物形象

	void ShowPlayerAct(PLAYER_ACT_TYPE iActType, int iLoopCount = 1);//播放对应类型的动画

private:
	virtual void onEnter();

	virtual void onExit();

	void OnPlayerActTimer(float dt);

	static vector<PlayerHead*> m_vcUsePlayerHead;

	CCSprite* m_pSpiriteHead;

	PLAYER_ACT_TYPE m_PlayerActType;

	int m_iActLoopCount;

	int m_iImageIndex;

	int m_iFrameIndex;

	CCSpriteFrameCache* cache;

	unsigned int m_lastTime;
};

#endif

