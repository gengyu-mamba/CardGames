#include "HelloWorldScene.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

// on "init" you need to initialize your instance
void HelloWorld::onEnter()
{   
	CCScene::onEnter();

	PlayerActLayer* player = new PlayerActLayer();
	player->autorelease();
	addChild(player);

	scheduleUpdate();			//启用每帧update调用
}

void HelloWorld::update(float dt)
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
