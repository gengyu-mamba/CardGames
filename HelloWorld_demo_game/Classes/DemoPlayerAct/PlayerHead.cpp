#include "PlayerHead.h"

//初始化每个玩家每个动作的帧数;
const int g_iActFrameNum[8][5] =
{
	{ 5, 5, 6, 8, 6 },
	{ 11, 4, 22, 8, 5 },
	{ 7, 4, 16, 8, 17 },
	{ 6, 5, 6, 6, 7 },
	{ 13, 5, 15, 6, 6 },
	{ 5, 9, 5, 8, 16 },
	{ 7, 9, 7, 10, 4 },
	{ 7, 9, 9, 7, 8 }
};

vector<PlayerHead*> PlayerHead::m_vcUsePlayerHead;

PlayerHead::PlayerHead()
{
	m_pSpiriteHead = NULL;

	m_iImageIndex = -1;

	m_iFrameIndex = 0;

	m_lastTime = 0;

	m_vcUsePlayerHead.push_back(this);

	cache = CCSpriteFrameCache::sharedSpriteFrameCache();
}

PlayerHead::~PlayerHead()
{
	for (int i = 0; i < m_vcUsePlayerHead.size(); i++)
	{
		if (m_vcUsePlayerHead[i] == this)
		{
			m_vcUsePlayerHead.erase(m_vcUsePlayerHead.begin() + i);
			break;
		}
	}
	RemoveImage();
}

void PlayerHead::onEnter()
{
	CCLayer::onEnter();

	schedule(schedule_selector(PlayerHead::OnPlayerActTimer), 0.3f);	//启动0.3秒定时器

	//被addChild的时候，如果没有创建人物，则随机创建一个
	if (m_pSpiriteHead == NULL)
	{
		InitImage();
	}
}

void PlayerHead::onExit()
{
	CCLayer::onExit();
}

void PlayerHead::OnPlayerActTimer(float dt)
{
	if (m_pSpiriteHead == NULL)
		return;

	if (m_iFrameIndex >= g_iActFrameNum[m_iImageIndex][m_PlayerActType])	//状态帧数结束
	{
		m_iFrameIndex = 0;
		if (m_iActLoopCount > 0)		//有循环次数继续循环播放
		{
			m_iActLoopCount--;
		}

		if (m_iActLoopCount == 0)	//循环结束从3个Normal状态里随机一个
		{
			m_PlayerActType = (PLAYER_ACT_TYPE)(rand() % 3);
			m_iActLoopCount = 1;
		}
	}
	//显示对应的状态帧
	char path[32];
	sprintf(path, "%d-%d-%d.png", m_iImageIndex, m_PlayerActType, m_iFrameIndex);
	CCSpriteFrame *pFrame = cache->spriteFrameByName(path);
	m_pSpiriteHead->setDisplayFrame(pFrame);
	m_iFrameIndex++;
}

int PlayerHead::GetUniqueImageIndex()
{
	int i, j;
	vector<int> vcUnUsePlayerIndex;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < m_vcUsePlayerHead.size(); j++)
		{

			if (i == m_vcUsePlayerHead[j]->GetImageIndex())
				break;

		}
		if (j == m_vcUsePlayerHead.size())
		{
			vcUnUsePlayerIndex.push_back(i);
		}
	}
	int iRand = rand() % vcUnUsePlayerIndex.size();
	int iImageIndex = vcUnUsePlayerIndex[iRand];

	return iImageIndex;
}

void PlayerHead::InitImage(int iImageIndex /*= -1*/)
{
	RemoveImage();
	if (iImageIndex == -1)
	{
		m_iImageIndex = GetUniqueImageIndex();
	}
	else
	{
		m_iImageIndex = iImageIndex;
	}
	m_PlayerActType = NORMAL_ACT_1;
	m_iActLoopCount = 1;
	m_iFrameIndex = 0;

	char path[32];
	sprintf(path, "player-%d.plist", m_iImageIndex);
	//cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(path);//添加plist进缓存

	//初始化m_pSpriteHead
	char spath[32];
	sprintf(spath, "%d-0-0.png", m_iImageIndex);
	CCSpriteFrame *pFrame = cache->spriteFrameByName(spath);
	if (m_pSpiriteHead == NULL)
	{
		
		m_pSpiriteHead = CCSprite::createWithSpriteFrame(pFrame);
		m_pSpiriteHead->retain();
	}
	else
	{
		m_pSpiriteHead->setDisplayFrame(pFrame);
	}
	addChild(m_pSpiriteHead);

}

void PlayerHead::RemoveImage()
{
	if (m_pSpiriteHead)
	{
		removeChild(m_pSpiriteHead,true);
		m_pSpiriteHead->release();

		char path[32];
		sprintf(path, "player-%d.plist", m_iImageIndex);
		cache->removeSpriteFramesFromFile(path);
	}
	m_pSpiriteHead = NULL;
	m_iImageIndex = -1;
}

void PlayerHead::ShowPlayerAct(PLAYER_ACT_TYPE iActType, int iLoopCount /*= 1*/)
{
	m_PlayerActType = iActType;
	m_iActLoopCount = iLoopCount;
	m_iFrameIndex = 0;
}

