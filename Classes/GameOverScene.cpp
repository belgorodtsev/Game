#include <ui/UIDeprecated.h>
#include "GameOverScene.h"
#include "HelloWorldScene.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;


Scene *GameOverScene::createScene() 
{
    auto scene = Scene::create();
    GameOverScene* layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init() 
{
    if (!Layer::init()) 
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameOVerLabel = Label::createWithTTF("Game over!", "textGame.ttf", 50);
    gameOVerLabel->setTextColor(Color4B::WHITE);
    gameOVerLabel->retain();

    auto startAgainLabel = Label::createWithTTF("Play again", "textGame.ttf",  40);
    startAgainLabel->setTextColor(Color4B::WHITE);
    startAgainLabel->retain();

    auto ScoreLabel = Label::createWithTTF("Score :",  "textGame.ttf", 30);
    
    ScoreLabel->setString(CCString::createWithFormat("Score: %d", getScore())->getCString());
    startAgainLabel->setTextColor(Color4B::WHITE);
    startAgainLabel->retain();

    auto playAgainItem = MenuItemLabel::create(startAgainLabel,
        CC_CALLBACK_1(GameOverScene::startAgainCallback, this));

    auto menu = Menu::create(playAgainItem, NULL);

    gameOVerLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 + gameOVerLabel->getContentSize().height * 3);
    menu->setPosition(visibleSize.width / 2, gameOVerLabel->getPosition().y - gameOVerLabel->getContentSize().height);
    ScoreLabel->setPosition(visibleSize.width / 2, gameOVerLabel->getPosition().y - gameOVerLabel->getContentSize().height * 2);

    this->addChild(gameOVerLabel);
    this->addChild(menu);
    this->addChild(ScoreLabel);

    return true;
}

size_t GameOverScene::getScore() const
{
    std::ifstream ifs("score.txt");
    std::string line;
    size_t score = 0;
    std::getline(ifs, line);
    score = atoi(line.c_str());
    line.clear();
    ifs.close();
    return score;
}

void GameOverScene::startAgainCallback(Ref *pSender)
{
    Director::getInstance()->replaceScene(
        TransitionFade::create(0.5, HelloWorld::createScene(), Color3B(255, 255, 255)));
}