#include "DemoLayer.h"
#include <string>
#include <cstdlib>

//��ʼ�����5��������֡����5�������ֱ���(��ͨ1����ͨ2����ͨ3��ʧ����ʤ��)
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

	//����ʱ��ԤԼ��������ʵ���Ǹ���ʱ���ˣ�ÿ��ִ��һ��OnSecondsTimer������
	//�������彨�黹�ǲ�Ҫ��̫�ඨʱ����ͨ��Ĭ�ϵ�ÿ֡�����update������һ������ʵ�ֶ�ʱЧ��
	schedule(schedule_selector(DemoLayer::OnSecondsTimer), 1.0f);

	scheduleUpdate();			//����ÿ֡update����

	setTouchEnabled(true);	//�������Layer���ܴ�������꣩�¼�

	//��ӱ���ͼ����ʾ����ͼƬ��ʾ����,��Դ��Ĭ��ָ����ResourcesĿ¼����ע��ֱ��ʹ��ͼƬ��Դ�����ĵ���CCImageSprite
	CCSprite *pSpriteBG = CCSprite::create("bg.jpg");//������������new CCSprite���󣬴󲿷����־�̬��������������˵�
	pSpriteBG->setPosition(ccp(1016 / 2, 703 / 2));	//���򴰿�����ԭ�㣨0,0��λ�����½ǣ���������������õ���ͼƬ���ĵ�λ��
	addChild(pSpriteBG);	//ע��addChild�����е���ʾ���󶼱��뱻���������addChild��Żᱻ��ʾ�������Ӷ����onEnter�ᱻ����

	////�����ʾ��꣨��������Ϣ
	m_pLableTouchInfo = CCLabelTTF::create("please click mouse to see click info", "Arial", 24);//GCLableText::lableTextWithString();
	m_pLableTouchInfo->setPosition(ccp(300, 100));
	addChild(m_pLableTouchInfo);

	////���ͼƬ������ʾ
	m_pLableNum = CCLabelAtlas::create("01234","clocknum.png",18,28,'0');
	m_pLableNum->setPosition(ccp(700, 380));
	addChild(m_pLableNum);

	//��Ӱ�ť,����ֻ��ʾ��ͼƬ��ӣ�pList��Ӧ��SpriteFrameģʽ����Լ�����
	m_pBtnTest = CCMenuItemImage::create("score-1-1.png", "score-1-2.png", "score-1-3.png", this, menu_selector(DemoLayer::OnBtnTest));	//������(Ĭ��ͼƬ�����ͼƬ������ͼƬ�������󣬵����ť�ص�����)
	m_pBtnTest->setPosition(ccp(1016 / 2, 703 / 2));

	CCMenu* pMenu = CCMenu::create(m_pBtnTest, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
	
	//
	////���������Դ��pList��(����IOS��һ��ƴͼ���߰Ѷ���pngͼƬ��ϳ�һ��ͼƬ��������plist�ļ���˵�����浥��ͼƬ����Ϣ��
	////���Կ�����Դ��player-0.plist��player-0.png��ǰ�߾���˵������ԭʼ��ͼ��XML��Ϣ(��ͼ�����ߴ磬��ƴͼ�е�λ��)���������ı��༭����plist���¾�������)
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("player-0.plist");//���plist������

	////���ݵ�ͼ�����ƻ�ȡplist��ĵ�ͼ����
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("0-0-0.png");
	CCSprite *pSpriteHead = CCSprite::createWithSpriteFrame(pFrame);	//���ݵ�ͼ����֡����Sprite��ͨ��plist֡�����Ŀ���ֱ����CCSprite��

	pSpriteHead->setPosition(ccp(300, 500));
	addChild(pSpriteHead);

	////��ӿɶ�������ͷ��
	m_pSpriteHeadAni = CCSprite::createWithSpriteFrameName("0-0-0.png");//ֱ�Ӹ��ݵ�ͼ����֡������Sprite��������ʵ����ִ����ͬ�ϵ�����
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
	if (nowTime - lastTime >= 500)	//���500MS�����
	{
		lastTime = nowTime;

		char szName[32];
		sprintf(szName, "0-%d-%d.png", iActTypeIndex, iFrameIndex);
		CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(szName);//ȡ�ö�Ӧ��Ҫ��ʾ��SpriteFrame��
		m_pSpriteHeadAni->setDisplayFrame(pFrame);	//������ʾ��Ӧ֡

		iFrameIndex++;	//������֡
		if (iFrameIndex >= g_iActFrameNum[iActTypeIndex])	//ͬ������֡��������
		{
			iFrameIndex = 0;	//֡����0
			iActTypeIndex++;	//�����¸�����
			if (iActTypeIndex >= 5)
			{
				iActTypeIndex = 0;
			}
		}
		char str[2];
		//m_pLableNum->setNum(iActTypeIndex);		//����ͼƬ��ʾ��ǰ�Ķ�������
		m_pLableNum->setString(itoa(iActTypeIndex,str,10));
	}
}

void DemoLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches�Ǹ��������������˶�㴥����Ϣ
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	char strPos[256];
	sprintf(strPos, "more ccTouchesBegan (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//��ʾ�ı��ַ���
}

void DemoLayer::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches�Ǹ��������������˶�㴥����Ϣ
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	char strPos[256];
	sprintf(strPos, "more ccTouchesMoved (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//��ʾ�ı��ַ���
}

void DemoLayer::ccTouchesEnded(CCSet* pTouches, CCEvent* pEvent)
{
	CCSetIterator it = pTouches->begin();		//pTouches�Ǹ��������������˶�㴥����Ϣ
	CCPoint ptLogic = CC_POINT_POINTS_TO_PIXELS(convertTouchToNodeSpace((CCTouch*)(*it)));	//�߼����꣬�����½�Ϊ��0,0��

	char strPos[256];
	sprintf(strPos, "more ccTouchesEnded (%d,%d)", (int)ptLogic.x, (int)ptLogic.y);
	m_pLableTouchInfo->setString(strPos);								//��ʾ�ı��ַ���
}

void DemoLayer::OnBtnTest(CCObject *pBtn)
{
	m_pBtnTest->setEnabled(false);	//�����ť����
}

void DemoLayer::OnSecondsTimer(float dt)
{
	//ÿ3����һ�ΰ�ť״̬�����õĻ�������
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