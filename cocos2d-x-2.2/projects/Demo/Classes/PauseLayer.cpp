#include "PauseLayer.h"
#include "HelloWorldScene.h"

PauseLayer::PauseLayer()
{

}

PauseLayer::~PauseLayer()
{

}

bool PauseLayer::init()
{
    bool bRet = true;

    do 
    {
        if (!CCLayer::init())
        {
            bRet = false;
            break;
        }

        //add a background
        CCSprite *bgSprite = CCSprite::create("game/bg.png");
        bgSprite->setAnchorPoint(CCPointZero);
        this->addChild(bgSprite);


        //init the menu
        CCMenuItemFont* resumeItem = CCMenuItemFont::create("resume",this,menu_selector(PauseLayer::resumeGame));
        resumeItem->setPosition(ccp(160,240));

        CCMenuItemFont* restartItem = CCMenuItemFont::create("restart", this, menu_selector(PauseLayer::restartGame));
        restartItem->setPosition(ccp(160,240));

        CCMenu* menu = CCMenu::create(resumeItem,restartItem,NULL);
        menu->alignItemsVertically();
        menu->setPosition(ccp(160,240));
        this->addChild(menu);

        menu->setTouchPriority(kCCMenuHandlerPriority - 2);
        

        //enable touch event
        this->setTouchEnabled(false);
        this->setVisible(false);
        this->setTouchPriority(kCCMenuHandlerPriority - 1);
       this->setTouchMode(kCCTouchesOneByOne);
        
    } while (0);

    return bRet;
}

bool PauseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCLOG("touch began");
    return true;
}

void PauseLayer::resumeGame(CCObject* obj)
{
    CCDirector::sharedDirector()->resume();
    this->hide();
}

void PauseLayer::show()
{
    this->setTouchEnabled(true);
    this->setVisible(true);
}

void PauseLayer::hide()
{
    this->setTouchEnabled(false);
    this->setVisible(false);
}

void PauseLayer::restartGame(CCObject* obj)
{
    //don't forget to call resume
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}