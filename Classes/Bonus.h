#pragma once
#include "cocos2d.h"
#include "GameObject.h"
#include "Player.h"
using namespace cocos2d;

class Bonus : public GameObject
{
public:
    Bonus(Point pos, const std::string & filenamePicture);
};

