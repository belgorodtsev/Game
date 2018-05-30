#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"  

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }
    // Background music
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background_music.mp3", true);

    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    setKeyboardEnabled(true);

    // Scrolling background
    scroll_sprire1 = Sprite::create("scrolling.jpg");
    scroll_sprire1->setAnchorPoint(Point(0, 0));
    scroll_sprire1->setPosition(size.width * 0.5f, size.height * 0.5f);
    this->addChild(scroll_sprire1);

    scroll_sprire2 = Sprite::create("scrolling.jpg");
    scroll_sprire2->setAnchorPoint(Point(0, 0));
    scroll_sprire1->setPosition(size.width * 0.5f, 0);
    this->addChild(scroll_sprire2);
   
    this->schedule(schedule_selector(HelloWorld::scroll), 0.001);
    
    // Add player 
    player = new Player(9.5f, 5.0f, Point(size.width / 4, 75), "player.png");
    this->addChild(player->getSprite());
    player->updateLifePlayer(false);
    // Physics Body
  
    player->PhysicsObject(false, (int)PhysicsCategory::Projectiles, (int)PhysicsCategory::None, (int)PhysicsCategory::All);
    
    this->schedule(schedule_selector(HelloWorld::updateScene)); 
    this->schedule(schedule_selector(HelloWorld::addLaser), 2.5 + rand() % 2);
    this->schedule(schedule_selector(HelloWorld::addRocket), 6 + rand() % 3);
    this->schedule(schedule_selector(HelloWorld::addBonus), 15 + rand() % 10);
    this->schedule(schedule_selector(HelloWorld::addCoins), 3 + rand() % 10);

    // Label score
    Score = 0;
    labelScore = LabelTTF::create("Score: 0", "textGame.ttf", 30.0);
    labelScore->cocos2d::CCNode::setAnchorPoint(ccp(1, 0));
    labelScore->setColor(Color3B::WHITE);
    labelScore->setPosition(Point(size.width, size.height - 35));
    this->addChild(labelScore);
    
    // Label coins
    size_coin = 0;
    labelCoins = LabelTTF::create("Coins: 0", "textGame.ttf", 30.0); 
    labelCoins->cocos2d::CCNode::setAnchorPoint(ccp(1, 0));
    labelCoins->setColor(Color3B::WHITE);
    labelCoins->setPosition(Point(size.width, size.height - 70));
    this->addChild(labelCoins);

    // Listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    this->stopAllActions();
    this->setScale(0.01f);
    this->runAction(ScaleBy::create(0.5f, 100.0f));

    return true;
}

void HelloWorld::scroll(float interval)
{
    Size size = Director::getInstance()->getVisibleSize();
    
    Point pos1 = scroll_sprire1->getPosition();
    Point pos2 = scroll_sprire2->getPosition();

    pos1.x -= (0.55 * size.height * interval);
    pos2.x -= (0.55 * size.height * interval);

    if (pos1.x <= -(size.width))
        pos1.x = pos2.x + size.width;

    if (pos2.x <= -(size.width))
        pos2.x = pos1.x + size.width;

    scroll_sprire1->setPosition(pos1);
    scroll_sprire2->setPosition(pos2);
   
};

bool HelloWorld::onContactBegan(PhysicsContact &contact) 
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if (nodeA->getTag() == (int)TegCategory::Enemy)
    {
        if (player->life_Info() == false)
        {
            SaveScore("score.txt");
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameOverScene::createScene(), Color3B(255, 0, 0)));
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dead.mp3");
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("smb_fireworks.mp3");
        player->unUpdateBonusPlayer();
    }
    else if (nodeB->getTag() == (int)TegCategory::Enemy)
    {
        if (player->life_Info() == false)
        {
            SaveScore("score.txt");
            Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameOverScene::createScene(), Color3B(255, 0, 0)));
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dead.mp3");
        }
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("smb_fireworks.mp3");
        player->unUpdateBonusPlayer();
    }
    else if (nodeA->getTag() == (int)TegCategory::Bonus)
    {
        nodeA->removeFromParent();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bonus_music.mp3");
        player->updateBonusPlayer();
    }
    else if (nodeB->getTag() == (int)TegCategory::Bonus)
    {
        nodeB->removeFromParent();
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bonus_music.mp3");
        player->updateBonusPlayer();
    }
    else if (nodeA->getTag() == (int)TegCategory::Coins)
    {
        nodeA->removeFromParent();
        size_coin += 1;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin.mp3");
        labelCoins->setString(CCString::createWithFormat("Coins: %d", size_coin)->getCString());
    }
    else if (nodeB->getTag() == (int)TegCategory::Coins)
    {
        nodeB->removeFromParent();
        size_coin += 1;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin.mp3");
        labelCoins->setString(CCString::createWithFormat("Coins: %d", size_coin)->getCString());
    }
    return true;
}

void HelloWorld::addLaser(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
 
    laser = new Laser(Point(size.width + 100 + origin.x, origin.y + (50 + rand() % 450)), laser->getNumberLaser());
    laser->getSprite()->setTag(0);
    this->addChild(laser->getSprite());

    laser->PhysicsObject(true, (int)PhysicsCategory::Laser, (int)PhysicsCategory::None, (int)PhysicsCategory::Projectiles);
    this->updateLaser(delta);
}

void HelloWorld::addRocket(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 pos = player->getSprite()->getPosition();

    rocket = new Rocket(Point(size.width + 100 + origin.x, origin.y + pos.y), "rocket.png");
    rocket->getSprite()->setScale(0.5);
    rocket->getSprite()->setTag((int)TegCategory::Enemy);
    this->addChild(rocket->getSprite());

    rocket->PhysicsObject(true, (int)PhysicsCategory::Rocket, (int)PhysicsCategory::None, (int)PhysicsCategory::Projectiles);
    this->updateRocket(delta);
}

void HelloWorld::addBonus(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    bonus = new Bonus(Point(size.width + 100 + origin.x, origin.y + (50 + rand() % 450)), "bon.png");
    bonus->getSprite()->setScale(1.5);
    bonus->getSprite()->setTag((int)TegCategory::Bonus);
    this->addChild(bonus->getSprite());

    bonus->PhysicsObject(true, (int)PhysicsCategory::Bonus, (int)PhysicsCategory::None, (int)PhysicsCategory::Projectiles);
    this->updateBonus(delta);
}

void HelloWorld::addCoins(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    coin = new Coins(Point(size.width + 100 + origin.x, origin.y + (50 + rand() % 450)), "coin.png");
    coin->getSprite()->setScale(0.5);
    coin->getSprite()->setTag((int)TegCategory::Coins);
    this->addChild(coin->getSprite());

    coin->PhysicsObject(true, (int)PhysicsCategory::Bonus, (int)PhysicsCategory::None, (int)PhysicsCategory::Projectiles);
    this->updateCoins(delta);
}

void HelloWorld::updateScene(float delta) 
{
    Score += 1;
    labelScore->setString(CCString::createWithFormat("Score: %d", Score)->getCString());
    this->updatePlayer(delta);
}

void HelloWorld::updatePlayer(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
   
    if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_SPACE) != heldKeys.end())
    {
        Vec2 pos = player->getSprite()->getPosition();
        if (pos.y <= 490)
            pos.y += player->getJumpVelosity();
        player->getSprite()->setPosition(pos);
    }

    cocos2d::Vec2 pos = player->getSprite()->getPosition();
    if ((pos.x >= size.width / 4) && (pos.y >= 75))
    {        
         pos -= Point(0, player->getGravity());
         player->getSprite()->setPosition(pos);
    }
}

void HelloWorld::updateLaser(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 pos = laser->getSprite()->getPosition();

    if (Score > 0 && Score < 400)
        laser->setSpeed(6);
    else if (Score > 400 && Score < 2000)
        laser->setSpeed(5);
    else if (Score > 2000 && Score < 4000)
        laser->setSpeed(4);
    else if (Score > 4000)
        laser->setSpeed(3);

    auto moveByAction = MoveTo::create(laser->getSpeed(), Point(pos.x - size.width * 2, pos.y));
    laser->getSprite()->runAction(moveByAction);

    delete laser;
}

void HelloWorld::updateRocket(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 pos = rocket->getSprite()->getPosition();

    if (Score > 0 && Score < 400)
        rocket->setSpeed(4);
    else if (Score > 400 && Score < 2000)
        rocket->setSpeed(3);
    else if (Score > 2000 && Score < 4000)
        rocket->setSpeed(2);
    else if (Score > 4000)
        rocket->setSpeed(2);
    
    Vec2 pos1 = rocket->getSprite()->getPosition();
    auto moveByAction1 = MoveTo::create(rocket->getSpeed(), Point(pos1.x - size.width * 2, pos1.y));
    rocket->getSprite()->runAction(moveByAction1);

    delete rocket;
}

void HelloWorld::updateBonus(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 pos = bonus->getSprite()->getPosition();

    if (Score > 0 && Score < 400)
        bonus->setSpeed(6);
    else if (Score > 400 && Score < 2000)
        bonus->setSpeed(5);
    else if (Score > 2000 && Score < 4000)
        bonus->setSpeed(4);
    else if (Score > 4000)
        bonus->setSpeed(3);

    auto moveByAction2 = MoveTo::create(bonus->getSpeed() , Point(pos.x - size.width * 2, pos.y));
    bonus->getSprite()->runAction(moveByAction2);

    delete bonus;
}

void HelloWorld::updateCoins(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 pos = coin->getSprite()->getPosition();

    if (Score > 0 && Score < 400)
        coin->setSpeed(6);
    else if (Score > 400 && Score < 2000)
        coin->setSpeed(5);
    else if (Score > 2000 && Score < 4000)
        coin->setSpeed(4);
    else if (Score > 4000)
        coin->setSpeed(3);

    auto moveByAction2 = MoveTo::create(coin->getSpeed(), Point(pos.x - size.width * 2, pos.y));
    coin->getSprite()->runAction(moveByAction2);

    delete coin ;
}

void HelloWorld::SaveScore(const std::string& filename) const
{
    std::ofstream ofs(filename);
    ofs << Score << std::endl;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) 
    {
        heldKeys.push_back(keyCode);
    }
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}
