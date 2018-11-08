#include "HelloWorldScene.h"

#include "DemoBase/DemoLayer.h"
#include "DemoPlayerAct/PlayerActLayer.h"
#include "DemoCard/DealCardLayer.h"
#include "DemoGame/GameLayer.h"


HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

void HelloWorld::onEnter()
{
	CCScene::onEnter();

	GameLayer *pLayer = new GameLayer();

	pLayer->autorelease();		//变量是自己new出来的，这里也没有保存成员变量，所以不可能自己手动delete了，这里设置autorelease，则可以再Layer被remove时候自动delete，这个例子里可以这么简单的理解
	addChild(pLayer);	//加入作为子对象并且默认显示，会触发子对象的onEnter

	scheduleUpdate();			//启用每帧update调用
}

void HelloWorld::update(float delta)
{

}
