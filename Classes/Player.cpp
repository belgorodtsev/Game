#include "Player.h"

Player::Player(float jump, float gravity, Point pos, const std::string & filenamePicture)
    : GameObject(pos, filenamePicture)
    , PLAYER_JUMP_VELOCITY(jump)
    , GRAVITY(gravity)
{}

void Player::updateBonusPlayer()
{
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage("k1.png");
    getSprite()->setTexture(tex);
    getSprite()->setTextureRect(CCRectMake(0, 0, tex->getContentSize().width, tex->getContentSize().height));
    PLAYER_JUMP_VELOCITY = 14.0f;
    GRAVITY = 8.0f;
    life = true;
}

void Player::unUpdateBonusPlayer()
{
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage("player.png");
    getSprite()->setTexture(tex);
    getSprite()->setTextureRect(CCRectMake(0, 0, tex->getContentSize().width, tex->getContentSize().height));
    PLAYER_JUMP_VELOCITY = 9.5f;
    GRAVITY = 5.0f;
    life = false;
}

bool Player::life_Info() const
{
    return life;
}

void Player::updateLifePlayer(bool b)
{
    life = b;
}

float Player::getJumpVelosity() const
{
    return PLAYER_JUMP_VELOCITY;
}

float Player::getGravity() const
{
    return GRAVITY;
}