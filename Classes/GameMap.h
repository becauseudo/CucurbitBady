#ifndef __CucurbitBaby__GameMap__
#define __CucurbitBaby__GameMap__
#include "cocos2d.h"
USING_NS_CC;

class GameMap :public Node{
public:
	virtual bool init();
	CREATE_FUNC(GameMap);
public:
	void addTMXTiledMap();
private:
	void addPlayer();
	void mapUpdate(float dt);
public:
	TMXTiledMap * thisTmxMap;
};
#endif