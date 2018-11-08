#ifndef __POSITON_CONFIG_H__
#define __POSITON_CONFIG_H__

#include "cocos2d.h"
USING_NS_CC;

//人物头像
enum {
    PLAYER_LEFT = 0,
    PLAYER_ME = 1,
    PLAYER_RIGHT = 2,
    PLAYER_UP = 3,
    };
//倒计时时间
const int MAX_CLOCK_TIME = 3.5;


//窗口大小
const int g_iWindowWidth = 1016;
const int g_iWindowHeight = 703;

//人物头像位置
const CCPoint g_ptPlayerHead[] = {ccp(70,400),ccp(50,100),ccp(940,400),ccp(230,570)};

//出牌按钮位置
const CCPoint g_ptBtnSend= CCPoint(505,185);

//单张牌大小
const CCSize g_sizeSingleCard = CCSize(141,173);

//手牌区域的位置
const CCPoint g_ptHandCard[] = {ccp(60,285),ccp(0,80),ccp(890,285),ccp(190,495)};

//剩余牌张显示的位置
const CCPoint g_ptLeftCardNum[] = {ccp(50,285),ccp(0,0),ccp(880,285),ccp(180,495)};
//剩余牌张显示数字单大小
const CCSize g_sizeLeftCardNum = CCSize(14,18);

//自己手牌的牌间隔
const int g_iSelfHandCardGap = 30;
//自己手牌的缩放值
const float g_fSelfHandScale = 0.7f;
//自己手牌选中后出列的额外高度
const int g_iHandCardSelectY = 20;

//其他玩家手牌的间隔
const int g_iOtherHandCardGap = 3;
//其他玩家手牌缩放值
const float g_fOtherHandScale = 0.2f;

//出牌位置
const CCPoint g_ptSendCard[] = {ccp(210,300),ccp(512,240),ccp(820,300),ccp(340,510)};
//出牌的牌间隔
const int g_iSendCardGap = 25;
//出牌的显示缩放值
const float g_fSendCardScale = 0.4f;

//发牌初始所有牌的位置
const CCPoint g_ptDealCardIni = ccp(0,400);
//发牌初始所有牌的间隔
const int g_iDealCardIniGap = 5;
//发牌初始所有牌的缩放
const float g_fDealCardIniScale = 0.4f;

//底牌位置
const CCPoint g_ptBaseCard = ccp(0,600);
//底牌显示间隔
const int g_iBaseCardGap = 80;
//底牌缩放值
const float g_fBaseCardScale = 0.5f;

//时钟的显示位置
const CCPoint g_ptClock[] = {ccp(210,400),ccp(512,300),ccp(820,400),ccp(400,470)};
//时钟数字单大小
const CCSize g_sizeClockNum = CCSize(18,28);


#endif //__POSITON_CONFIG_H__


