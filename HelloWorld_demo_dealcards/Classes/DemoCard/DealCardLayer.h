#ifndef __DEAL_CARD_LAYER_H__
#define __DEAL_CARD_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SendCardLayer.h"
#include "HandCardLayer.h"

#include <vector>
using namespace std;

class DealCardLayer : public cocos2d::CCLayer
{
public:
	DealCardLayer();

	virtual ~DealCardLayer();

	void OnSelfSendCard(int iSendCardIndex[], int iSendNum);

private:
	virtual void onEnter();

	virtual void onExit();

	void OnDealCardTimer(float dt);

	SendCardLayer *m_pSendCardLayer;
	HandCardLayer *m_pHandCardLayer;

	vector<int> m_vcAllCardIndex;

};

#endif

