#pragma once
#include <cocos2d.h>
#include "GameObject.h"
#include <vector>

using namespace cocos2d;

class Rocket : public GameObject
{
public:
    Rocket(Point pos, const std::string & filenamePicture);
};
