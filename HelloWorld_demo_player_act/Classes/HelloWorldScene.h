#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "DemoPlayerAct/PlayerActLayer.h"
USING_NS_CC;
class HelloWorld : public cocos2d::CCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	HelloWorld();
	virtual ~HelloWorld();
    virtual void onEnter();  

	virtual void update(float dt);		//ÿ֡���ᴥ����update����
};

#endif // __HELLOWORLD_SCENE_H__
