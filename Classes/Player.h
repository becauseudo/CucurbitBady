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
	Sprite * playerSprite;//��ɫ����
public:
	void createRunAnim();
	void createJump1Anim();
	void createJump2Anim();
	void createAttackAnim();
	void jumpAction();
	void run();//���Ǳ���
	void jump1();//������Ծ
	void jump2();//������Ծ
	void attack();//���ǹ���


	PlayerState playerState;
	Rect getBoundingBox();
private:

	void callback_1(Object* sender);

	virtual void update(float dt);

};

#endif