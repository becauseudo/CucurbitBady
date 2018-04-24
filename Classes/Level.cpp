#include "Level.h"
#include "GameLayer.h"

bool Level::init(){
	if (!Layer::init()){
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	winSize = Director::getInstance()->getWinSize();
	addSprite();
	addBtn();
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(Level::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
void Level::addSprite(){
	auto levelSprite = Sprite::create("level/level.png");
	levelSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(levelSprite, 0);

	auto roadSprite = Sprite::create("level/luxian.png");
	roadSprite->setPosition(Vec2(visibleSize.width / 2+5 , (visibleSize.height / 2)-35 ));
	this->addChild(roadSprite, 0);
}
void Level::addBtn(){
	//创建button对象  
	btn_1 = Button::create("level/index.png");
	btn_1->addTouchEventListener(CC_CALLBACK_2(Level::buttonCallStart, this));//为按钮添加触摸事件监听  
	btn_1->setPosition(Vec2(100, 100));
	this->addChild(btn_1,2);
}
void Level::buttonCallStart(Ref* sender, Widget::TouchEventType type){
	if (type == Widget::TouchEventType::ENDED)
	{
		auto scene= GameLayer::createScene();
		TransitionScene *transition = TransitionFade::create(1.0f, scene);
		Director::getInstance()->replaceScene(transition);
	}
	
}