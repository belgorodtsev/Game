#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Bonus.h"
using namespace cocos2d;

class Coins : public Bonus
{
public:
    Coins(Point pos, const std::string & filenamePicture);
};

