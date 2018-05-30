#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameObject
{
public:
    GameObject(Point pos, const std::string & filenamePicture);
    
    cocos2d::Sprite *getSprite() const;

    void PhysicsObject(bool Dynamic, int CategoryBitmask, int CollisionBitmask, int ContactTestBitmask) const;

    void setSpeed(float s);
    float getSpeed() const;

    virtual ~GameObject() = default;
private:
    cocos2d::Sprite *View;
    float speed;
};

