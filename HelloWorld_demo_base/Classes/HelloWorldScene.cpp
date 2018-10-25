#include "HelloWorldScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
void HelloWorld::onEnter()
{
	CCLayer::onEnter();

	DemoLayer *pLayer = new DemoLayer();

	pLayer->autorelease();		//�������Լ�new�����ģ�����Ҳû�б����Ա���������Բ������Լ��ֶ�delete�ˣ���������autorelease���������Layer��removeʱ���Զ�delete����������������ô�򵥵����
	addChild(pLayer);	//������Ϊ�Ӷ�����Ĭ����ʾ���ᴥ���Ӷ����onEnter

	scheduleUpdate();			//����ÿ֡update����
}

void HelloWorld::update(float delta)
{
	static unsigned int lastTime = 0;

	cc_timeval now;
	CCTime::gettimeofdayCocos2d(&now, NULL);
	unsigned int nowTime = now.tv_sec * 1000 + now.tv_usec / 1000;

	if (lastTime == 0)
	{
		lastTime = nowTime;
	}

	if (nowTime - lastTime >= 6000)	//60����Ƴ������Ӷ��󣬶������Ӷ������removeChild
	{
		//this->removeAllChildrenWithCleanup(true);	//�������Ȼᴥ���Ӷ����onExit��Ȼ����Ϊ�Ӷ�����autorelease�ģ����Իᱻֱ��delete
	}
}
