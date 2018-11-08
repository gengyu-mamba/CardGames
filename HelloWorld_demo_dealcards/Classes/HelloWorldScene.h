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

	virtual void update(float dt);		//每帧都会触发的update函数

};

#endif // __HELLOWORLD_SCENE_H__
