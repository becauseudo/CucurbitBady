#include "GameStart.h"
#include "Level.h"

Scene* GameStart::createScene()
{
	// 'scene' is an autorelease object
	gameStartScene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameStart::create();

	// add layer as a child to scene
	gameStartScene->addChild(layer);

	// return the scene
	return gameStartScene;
}

bool GameStart::init(){
	if (!Layer::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	addBg();

	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	return true;
}
void GameStart::addBg(){
	auto BgSprite = Sprite::create("fm.jpg");
	BgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BgSprite, 0);

	auto name = Sprite::create("name.png");
	name->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 90));
	this->addChild(name, 1);

	auto label = Sprite::create("jr.png");
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 200));
	this->addChild(label, 1);
	

	// create a few Actions
	auto scaleBy = ScaleBy::create(1.0f, 1.3f);
	auto delay = DelayTime::create(0.01f);
	auto sequence = Sequence::create(scaleBy, delay,scaleBy->reverse(), nullptr);

	// run it
	label->runAction(RepeatForever::create(sequence));

	
	
}

bool GameStart::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto level=Level::create();
	gameStartScene->addChild(level);

	return false;
}

void GameStart::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void GameStart::onTouchEnded(Touch *touch, Event *unused_event)
{

}

