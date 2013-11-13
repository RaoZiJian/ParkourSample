#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "PauseLayer.h"

using namespace CocosDenshion;


USING_NS_CC;

HelloWorld::HelloWorld()
	:_bulletArray(NULL),
    _enemiesArray(NULL),
    _score(0)
{
   _bulletArray = CCArray::create();
   _bulletArray->retain();

   _enemiesArray = CCArray::create();
   _enemiesArray->retain();
}

HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE_NULL(_bulletArray);
    CC_SAFE_RELEASE_NULL(_enemiesArray);
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bg/bg.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game/shoot.plist");
	//CCDirector::sharedDirector()->setContentScaleFactor(2.0);

	//1. add background
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bgSprite = CCSprite::createWithSpriteFrameName("background.png");
    //bgSprite->setScale( 320.0f / 480);  //set scale
	bgSprite->setPosition(ccp(winSize.width / 2, 
		winSize.height / 2));
	this->addChild(bgSprite);

	//2. add a player
	_playerSprite= CCSprite::createWithSpriteFrameName("hero1.png");
	_playerSprite->setScale(0.5);
	_playerSprite->setPosition(ccp(winSize.width/2, _playerSprite->getContentSize().height));
	this->addChild(_playerSprite);

    
	
	//this->addEnemy();
	this->schedule(schedule_selector(HelloWorld::spawnEnemy),0.5f);

	float fireRate = 3.0f / 10.0;
	this->schedule(schedule_selector(HelloWorld::fireBullet), fireRate);

    this->scheduleUpdate();

    //add score
    _scoreLabel = CCLabelTTF::create("0","Arial",20);
    _scoreLabel->setPosition(ccp(160,440));
    _scoreLabel->setColor(ccRED);
    this->addChild(_scoreLabel,110);

    this->initPauseMenu();

	//add a layer above the game play scene
	_pauseLayer = PauseLayer::create();
	_pauseLayer->setPosition(CCPointZero);
    //promt that visibility will not effect the touch priority
    this->addChild(_pauseLayer);

	
	
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_music.mp3");
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.2);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0);

	return true;
}



bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = this->convertTouchToNodeSpace(pTouch);
    _prevPosition = pt;
    return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}

void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint pt = this->convertTouchToNodeSpace(pTouch);
    CCPoint offset = pt - _prevPosition;
    _playerSprite->setPosition(_playerSprite->getPosition() + offset);
    _prevPosition = pt;
}

void HelloWorld::addEnemy() {
     //add some randomnesss
	CCSprite *enemySprite = CCSprite::createWithSpriteFrameName("enemy0.png");

	float maxWidth = 320;
	float minWidth = enemySprite->getContentSize().width/2;
	float actualWidth = CCRANDOM_0_1() * (maxWidth - minWidth) + minWidth;
	enemySprite->setPosition(ccp(actualWidth, 480 - enemySprite->getContentSize().height / 2));
	
	this->addChild(enemySprite);

	//add to array
	enemySprite->setTag(1);
	_enemiesArray->addObject(enemySprite);

	//move the enemy
	//Note!! we should change it with CCMoveBy
        // we can also give the random times
	int minDuration = 2.0;
	int maxDuration = 4.0;
	int actualDuration = CCRANDOM_0_1() * (maxDuration - minDuration) + minDuration;
	CCMoveBy *action = CCMoveBy::create(2.0,ccp(0,-480));

	//let the enemy back to original and repeat the process
	CCCallFuncO *callback = CCCallFuncO::create(this,callfuncO_selector(HelloWorld::onEnemyReachEndOfScreen), enemySprite);
	CCSequence *sequence = CCSequence::create(action,callback,NULL);

	
	enemySprite->runAction(sequence);

}

void HelloWorld::onEnemyReachEndOfScreen(CCObject *obj)
{
	CCSprite *sprite = (CCSprite*)obj;
	sprite->removeFromParentAndCleanup(true);

	if (sprite->getTag() == 1)
	{
		_enemiesArray->removeObject(sprite);
	}
    
	if (sprite->getTag() == 2)
	{
		_bulletArray->removeObject(sprite);
	}
	
     
}

void HelloWorld::spawnEnemy(float dt)
{
     this->addEnemy();
}

void HelloWorld::fireBullet(float dt)
{
    //get the player position 
    CCPoint playerPosition = _playerSprite->getPosition();

    //create a bullet
    CCSprite *bulletSprite = CCSprite::createWithSpriteFrameName("bullet1.png");
    CCSize bulletSize = bulletSprite->getContentSize();
    CCPoint pt = playerPosition + ccp(0, bulletSize.height/2 + _playerSprite->getContentSize().height/2 );
    bulletSprite->setPosition(pt);
    this->addChild(bulletSprite);

   
	SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
    

    //add it to bullet array
    bulletSprite->setTag(2);
    _bulletArray->addObject(bulletSprite);


    //moveBy action
    CCMoveBy *move = CCMoveBy::create(1.0,ccp(0,480));
    CCCallFuncO *callback = CCCallFuncO::create(this,callfuncO_selector(HelloWorld::onEnemyReachEndOfScreen),bulletSprite);
    CCSequence *action = CCSequence::create(move, callback,NULL);

    bulletSprite->runAction(action);
}

void HelloWorld::update(float dt)
{
    this->collideDetection();

    _scoreLabel->setString(CCString::createWithFormat("%d",_score)->getCString());
}

void HelloWorld::collideDetection()
{
   

    //check the bullet and enemy
    CCArray *bulletToDeleted = CCArray::create();
    CCObject *obj;
    CCARRAY_FOREACH(_bulletArray,obj)
	{
        CCSprite *bullet = (CCSprite*)obj;

        CCObject *innerObj;
        CCArray *enemyToDeleted = CCArray::create();
        CCARRAY_FOREACH(_enemiesArray,innerObj)
		{
            CCSprite *enemy = (CCSprite*)innerObj;
            //todo: make the collide more precise
            if (enemy->boundingBox().intersectsRect(bullet->boundingBox()))
            {
                bulletToDeleted->addObject(bullet);
                enemyToDeleted->addObject(enemy);

            }
            //calculate the bounding box
			CCSize playerSize = _playerSprite->getContentSize() * 0.3;
			CCRect playerRect = _playerSprite->boundingBox();
			playerRect.size = playerSize;
			if (enemy->boundingBox().intersectsRect(playerRect))
			{
				GameOverScene *scene = GameOverScene::create();
				CCDirector::sharedDirector()->replaceScene(scene);
                //save score
                //get original score
                int score = CCUserDefault::sharedUserDefault()->getIntegerForKey("highScore");
                //save only when the score is large than the original score
                if (_score > score)
				{
					CCUserDefault::sharedUserDefault()->setIntegerForKey("highScore", _score);
				}
                
			}
            
		}

        if (enemyToDeleted->count() > 0)
        {
            CCObject *pObj;
            CCARRAY_FOREACH(enemyToDeleted,pObj)
			{
                CCSprite *sp = (CCSprite*)pObj;
                
                _enemiesArray->removeObject(sp);
                sp->removeFromParentAndCleanup(true);
                _score++;
			}
            enemyToDeleted->removeAllObjects();
        }
	}

    if (bulletToDeleted->count() > 0)
    {
        CCObject *pObj;
        CCARRAY_FOREACH(bulletToDeleted,pObj)
		{
            CCSprite *sp = (CCSprite*)pObj;
            _bulletArray->removeObject(sp);
            sp->removeFromParentAndCleanup(true);
		} 
        bulletToDeleted->removeAllObjects();
    }
    
        
}

void HelloWorld::pauseGame(CCObject* obj)
{
    CCLOG("pause game");
    CCDirector::sharedDirector()->pause();

    this->_pauseLayer->show();

	//pause music? if you do so , you must resume it


}



void HelloWorld::initPauseMenu()
{
    CCSprite *pauseSprite_no = CCSprite::createWithSpriteFrameName("game_pause_nor.png");
    CCSprite *pauseSprite_hi = CCSprite::createWithSpriteFrameName("game_pause_pressed.png");
    CCMenuItem *pauseItem = CCMenuItemSprite::create(pauseSprite_no,pauseSprite_hi,NULL,this,menu_selector(HelloWorld::pauseGame));
    pauseItem->setPosition(ccp(20,450));

    CCMenu *menu = CCMenu::create(pauseItem,NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}
