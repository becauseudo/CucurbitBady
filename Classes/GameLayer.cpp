#include "GameLayer.h"
#include "common.h"



int jumpTimes = 0; //��ǰ��Ծ����
int jumpTotal = 2; //�����Ծ����

Scene* GameLayer::createScene(){
	//��ʼ����Ϸ������
	auto * scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vec2(0, GRAVITY));
	
	
	
	//��ʼ����layer
	auto *layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init(){
	if (!Layer::init()){
		return false;
	}
	dropSpeed = 6;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	addBg();
	this->schedule(schedule_selector(GameLayer::backGroundUpdate), 0.02f);
	
	//��Ӱ�ť
	addBtn();

	//��Ӽ���
	addListener();

	

	//���õ�ͼ,Ĭ��ê�������½�
	gameMap = GameMap::create();
	gameMap->setPosition(origin.x, origin.y);
	this->addChild(gameMap, 1);

	//���player
	player = Player::create();
	player->setPosition(0,0);
	this->addChild(player, 2);


	test();

	//�����ײ���
	auto conactListener = EventListenerPhysicsContact::create();
	conactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(conactListener, this);

	this->scheduleUpdate();
	return true;
}
void GameLayer::addBg(){
	BgSprite1 = Sprite::create("gameLayer/background2.jpg");
	BgSprite1->setAnchorPoint(Point::ZERO);
	BgSprite1->setPosition(Point::ZERO);
	this->addChild(BgSprite1, 0);

	BgSprite2 = Sprite::create("gameLayer/background2.jpg");
	BgSprite2->setAnchorPoint(Point::ZERO);
	BgSprite2->setPosition(Point::ZERO);
	this->addChild(BgSprite2, 0);


	mountain1 = Sprite::create("gameLayer/bg1.png");
	mountain1->setAnchorPoint(Point::ZERO);
	mountain1->setPosition(Point::ZERO);
	this->addChild(mountain1, 0);

	mountain2 = Sprite::create("gameLayer/bg1.png");
	mountain2->setAnchorPoint(Point::ZERO);
	mountain2->setPosition(Point::ZERO);
	this->addChild(mountain2, 0);
}

void GameLayer::backGroundUpdate(float dt)
{
	BgSprite1->setPositionX(BgSprite1->getPositionX() - 0.65f);
	BgSprite2->setPositionX(BgSprite1->getPositionX()
		+BgSprite1->getContentSize().width );
	if (BgSprite2->getPositionX() <= 0.0f){
		BgSprite1->setPositionX(0.0f);
	}

	mountain1->setPositionX(mountain1->getPositionX() - 2.0f);
	mountain2->setPositionX(mountain1->getPositionX()
		+ mountain1->getContentSize().width);
	if (mountain2->getPositionX() <= 0.0f){
		mountain1->setPositionX(0.0f);
	}
}


void GameLayer::update(float dt)
{
	player->setPosition(player->getPositionX(), player->getPositionY() - dropSpeed);
	if (sp_1->getBoundingBox().intersectsRect(player->getBoundingBox())){
		jumpTimes = 0;
		dropSpeed = 0;
	}
	else{
		dropSpeed = 6;
	}

}

bool GameLayer::onTouchBegan(Touch *touch, Event *event){
	auto touchPoint = touch->getLocation();
	//����Ƿ����ڰ�ť����
	if (attBtn->getBoundingBox().containsPoint(touchPoint)){
		attBtn->setTexture(attBtnTextures.at(1));
		player->attack();
	}
	if (jumpTimes < jumpTotal&&jumpBtn->getBoundingBox().
		containsPoint(touchPoint)){
		//if (isSound){
			//������Ч
		//}
		jumpBtn->setTexture(jumpBtnTextures.at(1));
		if (jumpTimes == 0){
			player->jump1();
		}
		if (jumpTimes == 1){
			player->jump2();
		}
		jumpTimes++;
	}
	return true;
}
void GameLayer::onTouchEnded(Touch *touch, Event *event){
	auto touchPoint = touch->getLocation();
	//�ж����ͷŵ�ʱ���Ƿ��ڰ�ťȥ����
	if (attBtn->getBoundingBox().containsPoint(touchPoint)){
		attBtn->setTexture(attBtnTextures.at(0));
		//player->run();
	}
	if (jumpBtn->getBoundingBox().containsPoint(touchPoint)){
		jumpBtn->setTexture(jumpBtnTextures.at(0));
	}

}
void GameLayer::addBtn()
{
	attBtn = Sprite::create("button/attMenu.png");
	auto attBtn_1 = Sprite::create("button/attMenu.png")->getTexture();
	auto attBtn_2 = Sprite::create("button/attMenuLock.png")->getTexture();
	attBtnTextures.pushBack(attBtn_1);
	attBtnTextures.pushBack(attBtn_2);
	attBtn->setScale(0.9);
	attBtn->setPosition(origin.x + 100, origin.y + 80);
	this->addChild(attBtn, 2);

	jumpBtn = Sprite::create("button/jumpMenu.png");
	auto jumpBtn_1 = Sprite::create("button/jumpMenu.png")->getTexture();
	auto jumpBtn_2 = Sprite::create("button/jumpMenuLock.png")->getTexture();
	jumpBtnTextures.pushBack(jumpBtn_1);
	jumpBtnTextures.pushBack(jumpBtn_2);
	jumpBtn->setScale(0.9);
	jumpBtn->setPosition(origin.x + visibleSize.width - 100, origin.y + 80);
	this->addChild(jumpBtn, 2);
}

void GameLayer::addListener()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

//��ײ���
bool GameLayer::onContactBegin(const PhysicsContact &contact)
{
	jumpTimes = 0;//��ص���ͽ�����Ծ��������

	if (player->playerState == JUMP1||player->playerState==JUMP2){
		player->run();
	}
	return true;
}

Point GameLayer::tileCoordForPosition(Point pos)
{
	Size mapTiledNum = gameMap->thisTmxMap->getMapSize();
	Size tiledSize = gameMap->thisTmxMap->getTileSize();
	int x = pos.x / tiledSize.width;
	//cocos��Ĭ��Y�������������ϵģ�����Ҫ���һ���������
	int y = (700 - pos.y) / tiledSize.height;
	//����������㿪ʼ����
	if (x > 0){
		x -= 1;
	}
	if (y > 0){
		y -= 0;
	}
	return Point(x, y);
}

void GameLayer::test()
{
	sp_1 = Sprite::create();
	sp_1->setTextureRect(Rect(0, 0, 50, 50));
	sp_1->setPosition(225, 60);
	sp_1->setColor(Color3B::RED);
	this->addChild(sp_1, 2);

}

