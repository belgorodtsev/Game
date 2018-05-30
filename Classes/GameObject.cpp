#include "GameObject.h"

GameObject::GameObject(Point pos, const std::string & filenamePicture)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    View = Sprite::create(filenamePicture);
    View->setPosition(pos);
}

void GameObject::PhysicsObject(bool Dynamic, int CategoryBitmask, int CollisionBitmask, int ContactTestBitmask) const
{
    auto SizeObject = View->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(SizeObject.width, SizeObject.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(Dynamic);
    physicsBody->setCategoryBitmask(CategoryBitmask);
    physicsBody->setCollisionBitmask(CollisionBitmask);
    physicsBody->setContactTestBitmask(ContactTestBitmask);
    View->setPhysicsBody(physicsBody);
}

cocos2d::Sprite * GameObject::getSprite() const
{
    if (View == nullptr)
        throw std::runtime_error("sprite was not been loaded");

    return View;
}

void GameObject::setSpeed(float s)
{
    speed = s;
}

float GameObject::getSpeed() const
{
    return speed;
}

