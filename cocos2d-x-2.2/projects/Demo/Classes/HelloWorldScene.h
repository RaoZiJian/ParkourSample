#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer;

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(); 

    //add a contructor and destructor
    HelloWorld();
    ~HelloWorld();


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void pauseGame(CCObject*);
    

    void initPauseMenu();

    void addEnemy();
    void onEnemyReachEndOfScreen(CCObject *obj);

    void spawnEnemy(float dt);
    void fireBullet(float dt);
    void collideDetection();
    void update(float dt);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
private:
    CCSprite *_playerSprite;
    CCPoint  _prevPosition;
    CCLabelTTF* _scoreLabel;
    int     _score;

    //add array for collide detection
    CCArray *_enemiesArray;
    CCArray *_bulletArray;

    //add pause logic
    bool _bIsPausing;
    PauseLayer *_pauseLayer;
};

#endif // __HELLOWORLD_SCENE_H__
