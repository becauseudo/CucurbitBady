#ifndef __CucurbitBaby__GameStart__
#define __CucurbitBaby__GameStart__
#include "cocos2d.h"
USING_NS_CC;
static Scene* gameStartScene;
class GameStart:public Layer
{
public:
	
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameStart);
	void addBg();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

private:
	
	Size visibleSize;
	Vec2 origin;
};

#endif