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

	static int GetUniqueImageIndex();	//��ȡ���Ψһ��ͷ��

	void InitImage(int iImageIndex = -1); //��ʼ����������Ĭ��ֵ-1��ʾ��Ҫ���Ψһ��bCleanImage��ʾ�Ƿ���Ҫ����ͼ����Դ�����п���ͬʱ����PlayerHead����ʹ��ͬһͼƬ��ʱ������Ϊtrue�ͻ�������

	int GetImageIndex(){ return m_iImageIndex; }	//��ȡ���ﶯ������

	void RemoveImage();	//�Ƴ���������

	void ShowPlayerAct(PLAYER_ACT_TYPE iActType, int iLoopCount = 1);//���Ŷ�Ӧ���͵Ķ���

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

