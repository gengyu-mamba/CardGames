#include "HelloWorldScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
void HelloWorld::onEnter()
{
	CCLayer::onEnter();

	DemoLayer *pLayer = new DemoLayer();

	pLayer->autorelease();		//变量是自己new出来的，这里也没有保存成员变量，所以不可能自己手动delete了，这里设置autorelease，则可以再Layer被remove时候自动delete，这个例子里可以这么简单的理解
	addChild(pLayer);	//加入作为子对象并且默认显示，会触发子对象的onEnter

	scheduleUpdate();			//启用每帧update调用
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

	if (nowTime - lastTime >= 6000)	//60秒后移除所有子对象，对所有子对象调用removeChild
	{
		//this->removeAllChildrenWithCleanup(true);	//这里首先会触发子对象的onExit，然后因为子对象是autorelease的，所以会被直接delete
	}
}
