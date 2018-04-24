#ifndef __CucurbitBaby__Player__
#define __CucurbitBaby__Player__
#include "cocos2d.h"
#include "common.h"
USING_NS_CC;
using namespace std;

class Player :public Node{
public:
	bool jumpBool_1;
	bool jumpBool_2;
	virtual bool init();
	CREATE_FUNC(Player);
	Sprite * playerSprite;//½ÇÉ«¾«Áé
public:
	void createRunAnim();
	void createJump1Anim();
	void createJump2Anim();
	void createAttackAnim();
	void jumpAction();
	void run();//Ö÷½Ç±¼ÅÜ
	void jump1();//Ö÷½ÇÌøÔ¾
	void jump2();//Ö÷½ÇÌøÔ¾
	void attack();//Ö÷½Ç¹¥»÷


	PlayerState playerState;
	Rect getBoundingBox();
private:

	void callback_1(Object* sender);

	virtual void update(float dt);

};

#endif