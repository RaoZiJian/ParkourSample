#include "StartScene.h"
#include "HelloWorldScene.h"


StartScene::StartScene(void)
{
}


StartScene::~StartScene(void)
{
}

bool StartScene::init()
{
    bool bRet = true;
    do 
    {
        if (!CCLayer::init())
        {
            bRet = false;
            break;
        }

        CCMenuItemFont *menuItem = CCMenuItemFont::create("Play",this,menu_selector(StartScene::startGame));
        menuItem->setPosition(ccp(160,240));
        CCMenu *menu = CCMenu::create(menuItem,NULL);
        menu->setPosition(CCPointZero);


        this->addChild(menu);

    } while (0);

    return bRet;
}

void StartScene::startGame(CCObject* obj)
{
    CCScene *sc = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(sc);
}

CCScene* StartScene::scene()
{
    CCScene *sc = CCScene::create();
    CCLayer* layer = StartScene::create();
    sc->addChild(layer);

    return sc;
}
