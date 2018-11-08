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

	pLayer->autorelease();		//�������Լ�new�����ģ�����Ҳû�б����Ա���������Բ������Լ��ֶ�delete�ˣ���������autorelease���������Layer��removeʱ���Զ�delete����������������ô�򵥵����
	addChild(pLayer);	//������Ϊ�Ӷ�����Ĭ����ʾ���ᴥ���Ӷ����onEnter

	scheduleUpdate();			//����ÿ֡update����
}

void HelloWorld::update(float delta)
{

}
