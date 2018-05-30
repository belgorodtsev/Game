#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Bonus.h"
#include <fstream>
#include "Coins.h"
#include "Laser.h"
#include "Rocket.h"
#include <string>

class HelloWorld : public cocos2d::Layer
{
 public:

    void updateScene(float interval);
    void updatePlayer(float interval);
    void updateLaser(float interval);
    void updateRocket(float interval);
    void updateBonus(float interval);
    void updateCoins(float interval);

    void scroll(float interval);
   
    void addLaser(float interval);
    void addRocket(float interval);
    void addBonus(float interval);
    void addCoins(float interval);

    bool onContactBegan(PhysicsContact &contact);
    void SaveScore(const std::string& filename) const;

    static cocos2d::Scene* createScene();
    
    virtual bool init();
    CREATE_FUNC(HelloWorld);

 private:

    enum class PhysicsCategory
    {
        None = 0,
        Laser = (1 << 0),
        Rocket = (1 << 1),
        Bonus = (1 << 2),
        All = PhysicsCategory::Laser | PhysicsCategory::Rocket | PhysicsCategory::Bonus,
        Projectiles = (1 << 3),
    };

    enum class TegCategory
    {
        Enemy = 0,
        Bonus,
        Coins,
    };

    Player *player;

    Laser * laser;
    Rocket * rocket;
    Bonus * bonus;
    Coins * coin;

    Sprite *scroll_sprire1;
    Sprite *scroll_sprire2;

    LabelTTF *labelScore;
    size_t Score;
    LabelTTF *labelCoins;
    size_t size_coin;

    std::vector<EventKeyboard::KeyCode> heldKeys;

    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

#endif // __HELLOWORLD_SCENE_H__
