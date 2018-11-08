#include "PlayerActLayer.h"
#include <vector>
using namespace std;

PlayerActLayer::PlayerActLayer()
{
	memset(m_pPlayerHead, 0, sizeof(m_pPlayerHead));

	srand(time(NULL));
}


PlayerActLayer::~PlayerActLayer()
{
}

void PlayerActLayer::onEnter()
{
	CCLayer::onEnter();

	scheduleUpdate();

	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");
	pSpriteBG->setPosition(ccp(1016/2,703/2));
	addChild(pSpriteBG);

	//人物形象
	m_pPlayerHead[0] = new PlayerHead();
	addChild(m_pPlayerHead[0]);
	m_pPlayerHead[0]->setPosition(ccp(100, 300));

	m_pPlayerHead[1] = new PlayerHead();
	addChild(m_pPlayerHead[1]);
	m_pPlayerHead[1]->setPosition(ccp(500, 100));

	m_pPlayerHead[2] = new PlayerHead();
	addChild(m_pPlayerHead[2]);
	m_pPlayerHead[2]->setPosition(ccp(900, 300));

	m_pPlayerHead[3] = new PlayerHead();
	addChild(m_pPlayerHead[3]);
	m_pPlayerHead[3]->setPosition(ccp(500, 600));

	////添加人物资源（pList）(这是IOS下一个拼图工具把多张png图片组合成一张图片，并且在plist文件里说明里面单张图片的信息，
	////可以看到资源有player-0.plist和player-0.png，前者就是说明后者原始单图的XML信息(单图名，尺寸，在拼图中的位置)，可以用文本编辑器打开plist看下就明白了)
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("TUTU.plist");//添加plist进缓存
	
	//按钮
	m_pBtnHappy = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("score-2-1.png"), CCSprite::createWithSpriteFrameName("score-2-2.png"), CCSprite::createWithSpriteFrameName("score-2-3.png"), this, menu_selector(PlayerActLayer::OnBtnHappy));
	m_pBtnHappy->setPosition(ccp(250, 703 / 2));

	m_pBtnSad = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("score-3-1.png"), CCSprite::createWithSpriteFrameName("score-3-2.png"), CCSprite::createWithSpriteFrameName("score-3-3.png"), this, menu_selector(PlayerActLayer::OnBtnSad));
	m_pBtnSad->setPosition(ccp(250+150, 703 / 2));

	m_pBtnChangePlayer = CCMenuItemImage::create("modify_portrait_btn-0.png", "modify_portrait_btn-1.png", NULL, this, menu_selector(PlayerActLayer::OnBtnChangePlayer));
	m_pBtnChangePlayer->setPosition(ccp(250 + 400, 703 / 2));

	CCMenu* pMenu = CCMenu::create();
	pMenu->addChild(m_pBtnHappy);
	pMenu->addChild(m_pBtnSad);
	pMenu->addChild(m_pBtnChangePlayer);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
}

void PlayerActLayer::onExit()
{
	CCLayer::onExit();

	//手动new的对象都需要手动delete
	//CC_SAFE_DELETE(m_pPlayerHead[0]);
	//CC_SAFE_DELETE(m_pPlayerHead[1]);
	//CC_SAFE_DELETE(m_pPlayerHead[2]);
	//CC_SAFE_DELETE(m_pPlayerHead[3]);
}

void PlayerActLayer::update(float dt)
{

}

void PlayerActLayer::OnBtnHappy(CCObject *pBtn)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_pPlayerHead[i])
		{
			m_pPlayerHead[i]->ShowPlayerAct(HAPPY_ACT, 3);
		}
	}
}

void PlayerActLayer::OnBtnSad(CCObject *pBtn)
{
	for (int i = 0; i < 4; i++)
	{
		if (m_pPlayerHead[i])
		{
			m_pPlayerHead[i]->ShowPlayerAct(SAD_ACT, 3);
		}
	}
}

void PlayerActLayer::OnBtnChangePlayer(CCObject *pBtn)
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (m_pPlayerHead[i])
		{
			m_pPlayerHead[i]->RemoveImage();
		}
	}

	for (i = 0; i < 4; i++)
	{
		if (m_pPlayerHead[i])
		{
			m_pPlayerHead[i]->InitImage();
		}
	}
}

