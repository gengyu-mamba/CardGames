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

	scheduleUpdate();			//启用每帧update调用
}

void HelloWorld::update(float dt)
{
}


