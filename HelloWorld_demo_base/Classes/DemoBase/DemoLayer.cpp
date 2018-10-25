#include "DemoLayer.h"
#include <string>
#include <cstdlib>

//初始化玩家5个动作的帧数，5个动作分别是(普通1，普通2，普通3，失利，胜利)
const int g_iActFrameNum[5] = { 5, 5, 6, 8, 6 };

DemoLayer::DemoLayer()
{
}


DemoLayer::~DemoLayer()
{
}

void DemoLayer::onEnter()
{
	CCLayer::onEnter();

	//设置时间预约函数，其实就是个定时器了，每秒执行一次OnSecondsTimer函数，
	//不过总体建议还是不要用太多定时器，通过默认的每帧进入的update函数，一样可以实现定时效果
	schedule(schedule_selector(DemoLayer::OnSecondsTimer), 1.0f);

	scheduleUpdate();			//启用每帧update调用

	setTouchEnabled(true);	//允许这个Layer接受触摸（鼠标）事件

	//添加背景图（演示单张图片显示方法,资源都默认指定在Resources目录），注意直接使用图片资源创建的得是CCImageSprite
	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");//这个方法里面会new CCSprite对象，大部分这种静态创建函数都是如此的
	pSpriteBG->setPosition(ccp(1016 / 2, 703 / 2));	//程序窗口坐标原点（0,0）位于左下角，并且这个函数设置的是图片中心点位置
	addChild(pSpriteBG);	//注意addChild，所有的显示对象都必须被父对象调用addChild后才会被显示，并且子对象的onEnter会被触发

	////添加显示鼠标（触摸）信息
	m_pLableTouchInfo = CCLabelTTF::create("please click mouse to see click info", "Arial", 24);//GCLableText::lableTextWithString();
	m_pLableTouchInfo->setPosition(ccp(300, 100));
	addChild(m_pLableTouchInfo);

	////添加图片数字显示
	m_pLableNum = CCLabelAtlas::create("01234","clocknum.png",18,28,'0');
	m_pLableNum->setPosition(ccp(700, 380));
	addChild(m_pLableNum);

	//添加按钮,这里只演示单图片添加，pList对应的SpriteFrame模式添加自己尝试
	m_pBtnTest = CCMenuItemImage::create("score-1-1.png", "score-1-2.png", "score-1-3.png", this, menu_selector(DemoLayer::OnBtnTest));	//参数：(默认图片，点击图片，禁用图片，父对象，点击按钮回调函数)
	m_pBtnTest->setPosition(ccp(1016 / 2, 703 / 2));

	CCMenu* pMenu = CCMenu::create(m_pBtnTest, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
	
	//
	////添加人物资源（pList）(这是IOS下一个拼图工具把多张png图片组合成一张图片，并且在plist文件里说明里面单张图片的信息，
	////可以看到资源有player-0.plist和player-0.png，前者就是说明后者原始单图的XML信息(单图名，尺寸，在拼图中的位置)，可以用文本编辑器打开plist看下就明白了)
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("player-0.plist");//添加plist进缓存

	////根据单图的名称获取plist里的单图对象
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("0-0-0.png");
	CCSprite *pSpriteHead = CCSprite::createWithSpriteFrame(pFrame);	//根据单图对象帧创建Sprite，通过plist帧创建的可以直接是CCSprite了

	pSpriteHead->setPosition(ccp(300, 500));
	addChild(pSpriteHead);

	////添加可动的人物头像
	m_pSpriteHeadAni = CCSprite::createWithSpriteFrameName("0-0-0.png");//直接根据单图对象帧名创建Sprite，里面其实就是执行了同上的两行
	m_pSpriteHeadAni->setPosition(ccp(700, 500));
	addChild(m_pSpriteHeadAni);
}

void DemoLayer::onExit()
{
	CCLayer::onExit();
}

void DemoLayer::update(float dt)
{
	static int iFrameIndex = 0;
	static int iActTypeIndex = 0;

	static unsigned int lastTime = 0;
	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	unsigned int nowTime = now.tv_sec * 1000 + now.tv_usec / 1000;
	if (nowTime - lastTime >= 500)	//间隔500MS进入次
	{
		lastTime = nowTime;

		char szName[32];
		sprintf(szName, "0-%d-%d.png", iActTypeIndex, iFrameIndex);
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//取得对应需要显示的SpriteFrame，
		m_pSpriteHeadAni->setDisplayFrame(pFrame);	//设置显示对应帧

		iFrameIndex++;	//继续下帧
		if (iFrameIndex >= g_iActFrameNum[iActTypeIndex])	//同个动作帧数放完了
		{
			iFrameIndex = 0;	//帧数归0
			iActTypeIndex++;	//继续下个动作
			if (iActTypeIndex >= 5)
			{
				iActTypeIndex = 0;
			}
		}
		char str[2];
		//m_pLableNum->setNum(iActTypeIndex);		//数字图片显示当前的动作索引
		m_pLableNum->setString(itoa(iActTypeIndex,str,10));
	}
}

void DemoLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	char strPos[256];
	sprintf(strPos, "more ccTouchesBegan (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//显示文本字符串
}

void DemoLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	char strPos[256];
	sprintf(strPos, "more ccTouchesMoved (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//显示文本字符串
}

void DemoLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches是个容器，里面存放了多点触摸信息
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//逻辑坐标，以左下角为（0,0）

	char strPos[256];
	sprintf(strPos, "more ccTouchesEnded (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//显示文本字符串
}

void DemoLayer::OnBtnTest(CCObject *pBtn)
{
	m_pBtnTest->setEnabled(false);	//点击按钮禁用
}

void DemoLayer::OnSecondsTimer(float dt)
{
	//每3秒检查一次按钮状态，禁用的话则启用
	static int iCount = 0;
	iCount++;
	if (iCount % 3 == 0)
	{
		if (m_pBtnTest->isEnabled() == false)
		{
			m_pBtnTest->setEnabled(true);
		}
	}
}