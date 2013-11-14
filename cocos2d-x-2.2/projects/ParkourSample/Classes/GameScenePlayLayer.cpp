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
    winSize = CCDirector::sharedDirector()->getWinSize();
	this->running();
	this->setTouchEnabled(true);
	actionNum = ACTION_RUN;
	backgroundInit();

	//Add snow particle
	CCParticleSystem *particle = CCParticleSnow::create();
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("pictures/snow.png"));
	addChild(particle,5);

	this->scheduleUpdate();   

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
	armature = CCArmature::create("ChenXiaoGeRunning");
	armature->setScale(0.3);
	armature->getAnimation()->play("running");
	armature->getAnimation()->setSpeedScale(2.0f);
	armature->setAnchorPoint(ccp(0.5,0));
	addChild(armature,5);
	chenxiaogeArmature = armature;
	actionNum = ACTION_RUN;
}

void GameScenePlayLayer::runJump()
{  
 
}

void GameScenePlayLayer::backgroundInit()
{
	float winWidth = winSize.width;
	float winHeight = winSize.height;
    
	background = CCSprite::create("pictures/background.png");
	backgroundCopy = CCSprite::create("pictures/background.png");
	shop = CCSprite::create("pictures/shop.png");
	sun = CCSprite::create("pictures/sun.png");
	ground = CCSprite::create("pictures/snowGroound.png");;
    groundCopy = CCSprite::create("pictures/snowGroound.png");

	background->setAnchorPoint(ccp(0,0));
	backgroundCopy->setAnchorPoint(ccp(0,0));
	shop->setAnchorPoint(ccp(0,0));
	sun->setAnchorPoint(ccp(0,0));
	ground->setAnchorPoint(ccp(0,0));
	groundCopy->setAnchorPoint(ccp(0,0));

    resetBackground();
    sun->setPosition(ccp(winWidth/2, winHeight*0.7));

	addChild(background,0);
	addChild(backgroundCopy,0);
	addChild(shop,1);
	addChild(sun,6);
	addChild(ground,1);
	addChild(groundCopy,1);

	chenxiaogeArmature->setPosition((chenxiaogeArmature->getContentSize().width)*0.3, ground->getContentSize().height);
}


void GameScenePlayLayer::update(float dt)
{
  if(backgroundCopy ->getPosition().x>=0){

	  background->setPosition(ccp(background->getPosition().x-1, 0));
	  backgroundCopy->setPosition(ccp(backgroundCopy->getPosition().x-1, 0));
	  shop->setPosition(ccp(shop->getPosition().x-1.5, shop->getPosition().y));
	  ground->setPosition(ccp(ground->getPosition().x-1, 0));
	  groundCopy->setPosition(ccp(groundCopy->getPosition().x-1, 0));
  }else{

	  resetBackground();
  }
}

void GameScenePlayLayer::resetBackground()
{
	float winWidth = winSize.width;
	float winHeight = winSize.height;
    background->setPosition(ccp(0,0));
	backgroundCopy->setPosition(ccp(background->getPosition().x + background->getContentSize().width, 0));
	ground->setPosition(ccp(0,0));
	groundCopy->setPosition(ccp(ground->getPosition().x + ground->getContentSize().width, 0));
	shop->setPosition(ccp(winWidth, ground->getContentSize().height));
}