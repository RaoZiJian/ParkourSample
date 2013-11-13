#pragma once //note: this kind of precompile directive is not portable
#include "cocos2d.h"

using namespace cocos2d;
class StartScene :public CCLayer
{
public:
	StartScene(void);
	~StartScene(void);
    virtual bool init();
    CREATE_FUNC(StartScene);

    static CCScene* scene();

    void startGame(CCObject *obj);

    
};

