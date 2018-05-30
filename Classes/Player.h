#pragma once
#include "cocos2d.h"
#include "GameObject.h"
using namespace cocos2d;

class Player : public GameObject
{
public:  
    Player(float jump, float gravity, Point pos, const std::string & filenamePicture);

    void updateBonusPlayer();
    void unUpdateBonusPlayer();

    bool life_Info() const;
    void updateLifePlayer(bool b);

    float getJumpVelosity() const;
    float getGravity() const;

private:
    float PLAYER_JUMP_VELOCITY;
    float GRAVITY;
    bool life;
};