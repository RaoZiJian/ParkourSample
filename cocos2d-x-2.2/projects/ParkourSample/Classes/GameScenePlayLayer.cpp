//
//  GameScenePlayLayer.cpp
//  ChenXiaoGe
//
//  Created by Ken on 13-10-10.
//
//

#include "GameScenePlayLayer.h"
#include "GameScene.h"

#define ANIME_RUN 0
#define ANIME_JUMP 0

bool GameScenePlayLayer::init()
{
	playerX = 50.0;
    playerY = 70.0;
	this->running();
	this->setTouchEnabled(true);
	actionNum = ACTION_RUN;
    
    return true;
}

bool GameScenePlayLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
   
	return true;
}

void GameScenePlayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GameScenePlayLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScenePlayLayer::running()
{
	CCArmature *armature = NULL;
	armature = CCArmature::create("CMRun");
	armature->setScale(0.6);
	armature->getAnimation()->play("Running");
	armature->getAnimation()->setSpeedScale(2.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	armature->setPosition(ccp(playerX+30, playerY));
	addChild(armature);
	chenxiaogeArmature = armature;
	actionNum = ACTION_RUN;
}

void GameScenePlayLayer::runJump()
{  
 
}
