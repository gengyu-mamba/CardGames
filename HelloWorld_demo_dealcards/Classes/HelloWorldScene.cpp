#include "HelloWorldScene.h"

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

void HelloWorld::onEnter()
{
	CCScene::onEnter();

	DealCardLayer* pDealCard = new DealCardLayer();
	pDealCard->autorelease();
	addChild(pDealCard);

	scheduleUpdate();			//����ÿ֡update����
}

void HelloWorld::update(float dt)
{
}


