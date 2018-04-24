#include "GameMap.h"
#include "common.h"
#include "Player.h"

bool GameMap::init(){
	if (!Node::init()){
		return false;
	}

	addTMXTiledMap();
	


	//������ײ��
	//auto TmxBody = PhysicsBody::createBox(Size(size.width * 25, size.height*3.5));
 	//TmxBody->setPositionOffset(Vec2(400,50));//thisTmxMap->getPosition());
 	//TmxBody->setDynamic(false);
 	//TmxBody->setContactTestBitmask(1);
 	//TmxBody->setGravityEnable(false);
 	//TmxBody->getShape(0)->setRestitution(0);//���ø���ص���
 	//TmxBody->setRotationEnable(false);
 	//this->setPhysicsBody(TmxBody);
	
	return true;
}
void GameMap::addTMXTiledMap(){
	thisTmxMap = TMXTiledMap::create("gameLayer/s_1.tmx");
	this->addChild(thisTmxMap);
}

