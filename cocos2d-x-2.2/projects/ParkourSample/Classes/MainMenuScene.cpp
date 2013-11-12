//
//  MainMenuScene.cpp
//  ParkourSample
//
//  Created by Ken on 13-10-10.
//
//

#include "MainMenuScene.h"
#include "GameScene.h"

static bool isFirstInGame = true;
bool MainMenuScene::init()
{    
    CCLayer* menuLayer = CCLayer::create();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // Add backgrounbdPic
    CCSprite* backGroundPic = CCSprite::create("pictures/mainMenuBackGround.png");
    backGroundPic->setAnchorPoint(ccp(0, 0));
    
    menuLayer->addChild(backGroundPic,0);
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/ChenXiaoGeWelcome.ExportJson");

	CCArmature *armature = CCArmature::create("ChenXiaoGeWelcome");
	armature->getAnimation()->play("Animation1");
	armature->getAnimation()->setSpeedScale(1.5f);
	armature->setAnchorPoint(ccp(0,0));
	armature->setPosition(ccp(50, 50));
	armature->setScale(0.5);
	menuLayer->addChild(armature,1);

	this->addChild(menuLayer,0);
    
    //Add StartBtn
/*    CCSprite* start     = CCSprite::create("iphone/StartBtn.png");
    CCSprite* startPush = CCSprite::create("iphone/StartBtnPush.png");
    
    CCMenuItemSprite * startBtn = CCMenuItemSprite::create(start, startPush, this, menu_selector(MainMenuScene::startBtnCallFunc));
    
    //Add Menu
    mainMenu = CCMenu::create(startBtn, NULL);
    mainMenu->setAnchorPoint(ccp(0, 0));
    mainMenu->setPosition(ccp(size.width/2, size.height/5));

    menuLayer->addChild(mainMenu,1);
    this->addChild(menuLayer);
*/

    return true;
}

void MainMenuScene::startBtnCallFunc(CCObject* pSender)
{	
	loadingCount = 0;
	dataLoaded(loadingCount);

   
}
void MainMenuScene::dataLoaded(float percent)
{
	if(!isFirstInGame)
	{
		/*GameScene* gameScene =  GameScene::newGameScene();
		CCTransitionFade* gameSceneTransition =  CCTransitionFade::create(0.5, gameScene, ccWHITE);
		CCDirector::sharedDirector()->replaceScene(gameSceneTransition);
		*/
		return;
	}

	switch (loadingCount)
	{
		case ACTION_RUN:
		{
			CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync("animations/CMRun.ExportJson",this, schedule_selector(MainMenuScene::dataLoaded));
		}
		break;	
	default:
		{
			isFirstInGame = false;

		/*	CCScene * newscene  = CCScene::create();
			GameScene* gameScene =  GameScene::newGameScene();
			CCTransitionFade* gameSceneTransition =  CCTransitionFade::create(0.5, gameScene, ccWHITE);
			CCDirector::sharedDirector()->replaceScene(gameSceneTransition); */
		}
		break;
	}	
	loadingCount++;
	
}