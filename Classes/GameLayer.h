#ifndef __CucurbitBaby__GameStart__
#define __CucurbitBaby__GameStart__
#include "cocos2d.h"
#include "Player.h"
#include "GameMap.h"
USING_NS_CC;
class GameLayer :public Layer
{
public:

	int dropSpeed;

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void addBg();//Ìí¼Ó±³¾°
	virtual void update(float dt);
	GameMap *gameMap;
private:
	Size visibleSize;
	Vec2 origin;
	

	Player *player; //½ÇÉ«
	Sprite * BgSprite1, * BgSprite2, * mountain1, * mountain2;

private:
	void backGroundUpdate(float dt);
	bool onContactBegin(const PhysicsContact &contact);
	void addBtn();
	void addListener();
	//´¥Ãþ¼ì²â
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	Sprite* sp_1;
	Sprite* sp_2;

	void test();
private:
	Sprite * attBtn;
	Vector<Texture2D *> attBtnTextures;
	Sprite * jumpBtn;
	Vector<Texture2D *> jumpBtnTextures;

	Point tileCoordForPosition(Point pos);
};
#endif