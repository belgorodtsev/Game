#pragma once
#include <cocos2d.h>
#include "GameObject.h"
#include <vector>

using namespace cocos2d;

class Laser : public GameObject
{
public:
    Laser(Point pos, const std::string & filenamePicture);
    std::string getNumberLaser();
};
