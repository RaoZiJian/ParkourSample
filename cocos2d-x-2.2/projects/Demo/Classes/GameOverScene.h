#ifndef __GAME_OVER_SCENE__H
#define __GAME_OVER_SCENE__H


#include "cocos2d.h"

using namespace cocos2d;


class GameOverScene : public CCScene
{
public:
    GameOverScene();
    ~GameOverScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
};


class GameOverLayer : public CCLayerColor
{
public:
    GameOverLayer();
    ~GameOverLayer();
    virtual bool init();
    CREATE_FUNC(GameOverLayer);

    void restartGame(float dt);


};
#endif