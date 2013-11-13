#include "GameOverScene.h"
#include "HelloWorldScene.h"

GameOverScene::GameOverScene()
{

}

GameOverScene::~GameOverScene()
{

}

bool GameOverScene::init()
{
    bool bRet = true;

    do 
    {
        if (!CCScene::init())
        {
            bRet = false;
            break;
        }

        GameOverLayer *layer = GameOverLayer::create();
        this->addChild(layer);


    } while (0);

    return bRet;
}

GameOverLayer::GameOverLayer()
{

}

GameOverLayer::~GameOverLayer()
{

}


bool GameOverLayer::init()
{
    bool bRet = true;
    do 
    {
        if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
        {
            bRet = false;
            break;
        }

        CCLabelTTF *gameOverLabel = CCLabelTTF::create("Game Over", "Arial", 20);
        gameOverLabel->setPosition(ccp(160,340));
        gameOverLabel->setColor(ccBLACK);
        this->addChild(gameOverLabel);

        //read the high score and displayed
        int highScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("highScore");
        CCLabelTTF *highscoreLabel = CCLabelTTF::create(CCString::createWithFormat("You high score is:%d", highScore)->getCString(),"Arial", 30);
        highscoreLabel->setPosition(ccp(160,200));
        highscoreLabel->setColor(ccRED);
        this->addChild(highscoreLabel);

        this->scheduleOnce(schedule_selector(GameOverLayer::restartGame), 3.0);


    } while (0);
    return bRet;
}

void GameOverLayer::restartGame(float dt)
{
    CCScene *hello = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(hello);
}
