#pragma once

#include "HelloWorldScene.h"
#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
 public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    void startAgainCallback(cocos2d::Ref *pSender);
    size_t getScore() const;
    CREATE_FUNC(GameOverScene);
};  

