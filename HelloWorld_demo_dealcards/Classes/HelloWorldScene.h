#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DemoCard/DealCardLayer.h"
USING_NS_CC;

class HelloWorld : public cocos2d::CCScene
{
public:
	HelloWorld();

	virtual ~HelloWorld();

	virtual void onEnter();

	virtual void update(float dt);		//ÿ֡���ᴥ����update����

};

#endif // __HELLOWORLD_SCENE_H__
