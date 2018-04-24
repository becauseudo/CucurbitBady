#ifndef __CucurbitBaby__Level__
#define __CucurbitBaby__Level__
#include "cocos2d.h"
#include "ui\UIButton.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class Level :public Layer{
public:
	Button* btn_1;
public:
	virtual bool init();
	CREATE_FUNC(Level);
	void addSprite();
	void addBtn();
	void buttonCallStart(Ref* sender, Widget::TouchEventType type);

private:
	Size visibleSize;
	Vec2 origin;
	Size winSize;
};
#endif