#pragma  once

#include "cocos2d.h"

using namespace cocos2d;

class PauseLayer : public CCLayer
{
public:
    PauseLayer();
    ~PauseLayer();
    virtual bool init();
    CREATE_FUNC(PauseLayer);

     virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	void resumeGame(CCObject*);
	void restartGame(CCObject*);

    void show();
    void hide();

};

