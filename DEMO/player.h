#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include<graphics.h>

extern const float GROUND_Y;        //地面高度
extern const float GRAVITY;         //重力加速度(像素每二次方秒)
extern const float JUMP_SPEED;      //跳跃初速度(像素每秒)
extern const float MOVE_SPEED;      //水平移动速度                 

class Slime;
class Player 
{
	float x, y;    //坐标
	int hp=20;     //血量
	bool alive = true;
public:
	int getHP() const { return hp; }
	float getX() const { return x; }
	float getY() const { return y; }
	float vx, vy;  //速度

	Player(float x_0, float y_0);
	~Player() {}

	float Height, Width;
	float HitBoxW, HitBoxH;
	float hitDurationS;             //轻攻击持续时间
	float hitDurationH;             //重攻击持续时间
	float invincibleTimer;          //无敌时间
	float HurtTime;                 //硬直时间
	float attackTimerH;             //重攻击计数
	float attackTimerS;             //轻攻击计数
	float attackStartH;             //重攻击开始时间(起手式)
	float attackEndH;               //重攻击结束时间
	float attackStartS;             
	float attackEndS;

	bool isLeft;
	bool isOnGround = true;
	bool invincible = false;        //无敌
	bool getHurt = false;           //受伤
	bool isAttackingS = false;      //轻攻击
	bool isAttackingH = false;      //重攻击
	bool hasHit = false;            //确保只造成一次伤害 

	bool isAlive();
	bool checkSlimeCollision(const Slime& slime);    //碰撞箱检测
	void checkSlimeAttack(Slime& slime);             //对Slime的攻击
	void PhyUpdate(float dt);                        //状态更新
	void takeDamage(int num);                        //受击
	void onDeath();                                  //设置死亡
};

#endif