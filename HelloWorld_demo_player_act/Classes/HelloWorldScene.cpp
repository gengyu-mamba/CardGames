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

	scheduleUpdate();			//����ÿ֡update����
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

	if (nowTime - lastTime >= 6000)	//60����Ƴ������Ӷ��󣬶������Ӷ������removeChild
	{
		//this->removeAllChildrenWithCleanup(true);	//�������Ȼᴥ���Ӷ����onExit��Ȼ����Ϊ�Ӷ�����autorelease�ģ����Իᱻֱ��delete
	}
}
