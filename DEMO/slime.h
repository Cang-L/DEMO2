#pragma once
#ifndef SLIME_H
#define SLIME_H
#include<memory>
#include "player.h"
#include "animation.h" 

extern float spawnTimer;
extern const float SPAWN_INTERVAL;

class Slime
{
private:
	Animation Slime_WalkL;
	Animation Slime_WalkR;
	Animation Slime_IDLER;
	Animation Slime_IDLEL;
	Animation Slime_DeathL;
	Animation Slime_DeathR;

	float x, y;
	int hp = 2;
	const int SPEED = 100;
	const int chargeSpeed = 300;

public:
	float vx;

	bool isAttacking;
	bool isLeft;
	bool alive;
	bool getHurt;           //受伤(硬直)
	bool animeFinish;       //!isAlive()&&animeFinish 后 delete

	float attackTimer;      //攻击计数
	float attackCooldown;   //攻击间隔
	float attackDuration;   //攻击时长
	float attackStart;      //判定开始时间
	float attackEnd;        //判定结束时间
	float attackArea;       //攻击距离
	float hasAttacked;      //已攻击
	float cooldownTimer;    //攻击间隔计数
	float remainHurt;       //硬直计数

	Slime(float x_0, float y_0);

	float getX() const { return x; }
	float getY() const { return y; }

	void Move(const Player& player,float dt);        //跟踪玩家移动
	void takeDamage(int damage);
	void CheckPlayerAttack(const Player& player); //碰撞箱设置

	
	bool isAlive() const                             //检查是否存活
	{
		return alive;
	}

	void setDeath();

	void showSlime(float dt);
};

#endif