#include "Player.h"
#include "GameLayer.h"

//用的全局变量来存储游戏角色，后面全部改成配置文件
extern PlayerType playerType;

int jumpSpeed;
int jumpAddSpeed;
bool Player::init()
{
	if (!Node::init()){
		return false;
	}
	jumpBool_1 = false;
	jumpBool_2 = false;
	jumpSpeed = 20;
	jumpAddSpeed = 1;
	playerSprite = Sprite::create("run1.png");
	playerSprite->setPosition(220, 370);
	this->addChild(playerSprite, 2);
	//初始化四个动画
	createRunAnim();

	this->scheduleUpdate();
	return true;
}


void Player::run(){
	playerState = RUN;
	playerSprite->stopAllActions();
	createRunAnim();
}
void Player::jumpAction(){
	this->setPosition(this->getPositionX(), this->getPositionY() + jumpSpeed);
	jumpSpeed -= jumpAddSpeed;
}
void Player::jump1(){
	playerState = JUMP1;
	playerSprite->stopAllActions();
	createJump1Anim();
	jumpBool_1 = true;
	
}
void Player::jump2(){
	playerState = JUMP2;
	playerSprite->stopAllActions();
	createJump2Anim();
	jumpBool_2 = true;
}
void Player::attack(){
	playerState = ATTACK;
	playerSprite->stopAllActions();
	createAttackAnim();
	
}

void Player::createRunAnim()
{
	///将图片加载到精灵帧缓冲池 
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("run.plist");

	//建立精灵帧数组
	Vector<SpriteFrame*> mSprite;
	SpriteFrame* frame = NULL;
	char str[100] = { 0 };
	for (int i = 1; i < 8; i++)
	{
		sprintf(str, "run%d.png", i);
		frame = frameCache->spriteFrameByName(str);
		mSprite.pushBack(frame);
	}
	auto runAnimation = Animation::createWithSpriteFrames(mSprite, 0.1f);
	runAnimation->setLoops(-1);//设置循环，-1代表无限循环
	runAnimation->setRestoreOriginalFrame(true);//是否在动画播放结束后恢复到第一针
	auto runAnimate = Animate::create(runAnimation);
	playerSprite->runAction(runAnimate);
}
void Player::createJump1Anim()
{
	///将图片加载到精灵帧缓冲池 
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("jump_new.plist");

	//建立精灵帧数组
	Vector<SpriteFrame*> mSprite;
	SpriteFrame* frame = NULL;
	char str[100] = { 0 };
	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "jump_%d.png", i);
		frame = frameCache->spriteFrameByName(str);
		mSprite.pushBack(frame);
	}
	auto jump1Animation = Animation::createWithSpriteFrames(mSprite, 0.1f);
	auto jump1Animate = Animate::create(jump1Animation);
	auto act_2 = CallFuncN::create(CC_CALLBACK_1(Player::callback_1, this));
	auto end = Sequence::create(jump1Animate, act_2, NULL);
	playerSprite->runAction(end);
}
void Player::createJump2Anim()
{
	///将图片加载到精灵帧缓冲池 
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("jump_new.plist");

	//建立精灵帧数组
	Vector<SpriteFrame*> mSprite;
	SpriteFrame* frame = NULL;
	char str[100] = { 0 };
	for (int i = 11; i < 19; i++)
	{
		sprintf(str, "jump_%d.png", i);
		frame = frameCache->spriteFrameByName(str);
		mSprite.pushBack(frame);
	}
	auto jump2Animation = Animation::createWithSpriteFrames(mSprite, 0.1f);
	auto jump2Animate = Animate::create(jump2Animation);
	auto act_2 = CallFuncN::create(CC_CALLBACK_1(Player::callback_1, this));
	auto end = Sequence::create(jump2Animate, act_2, NULL);
	playerSprite->runAction(end);
}
void Player::createAttackAnim()
{
	///将图片加载到精灵帧缓冲池 
	auto frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("att.plist");

	//建立精灵帧数组
	Vector<SpriteFrame*> mSprite;
	SpriteFrame* frame = NULL;
	char str[100] = { 0 };
	for (int i = 1; i < 7; i++)
	{
		sprintf(str, "dun%d.png", i);
		frame = frameCache->spriteFrameByName(str);
		mSprite.pushBack(frame);
	}
	auto attackAnimation = Animation::createWithSpriteFrames(mSprite, 0.1f);
	auto attackAnimate = Animate::create(attackAnimation);
	auto act_2 = CallFuncN::create(CC_CALLBACK_1(Player::callback_1, this));
	auto end = Sequence::create(attackAnimate, act_2, NULL);
	playerSprite->runAction(end);
}

void Player::callback_1(Object* sender)
{
	createRunAnim();
}

Rect Player::getBoundingBox(){
	Rect rect = playerSprite->getBoundingBox();
	Vec2 vec = this->convertToWorldSpace(playerSprite->getPosition());
	float width = rect.size.width;
	float height = rect.size.height;
	return Rect(vec.x-width/2, vec.y-height/2, width, height);
}

void Player::update(float dt)
{
	if (jumpBool_1 == true){
		jumpAction();
		if (jumpBool_2==true){
			jumpSpeed+=15;
			jumpBool_2 = false;
		}
	}
	if (jumpSpeed < 0){
		jumpBool_1 = false;
		jumpSpeed = 20;
	}
}



