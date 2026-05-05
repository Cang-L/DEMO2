#pragma once
#ifndef SLIME_H
#define SLIME_H
#include<memory>
#include "player.h"
#include "animation.h" 

extern float spawnTimer;
extern const float SPAWN_INTERVAL;
extern int DeadSlimeNum;

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
	float Width;
	float Height;
	float HitBoxW;
	float HitBoxH;

	bool isAttacking;       //正在攻击
	bool isLeft;
	bool alive;
	bool getHurt;           //受伤(硬直)
	bool animeFinish;       //!isAlive()&&animeFinish 后 delete
	bool invincible;        //无敌

	float attackTimer;      //攻击计时
	float attackCooldown;   //攻击间隔
	float attackDuration;   //攻击时长
	float attackStart;      //判定开始时间
	float attackEnd;        //判定结束时间
	float attackArea;       //攻击距离
	float hasAttacked;      //已攻击
	float cooldownTimer;    //攻击间隔计时
	float remainHurt;       //硬直计时
	float deathAnimeTimer;  //死亡动画计时
	float invincibleTimer;  //无敌时间


	Slime(float x_0, float y_0);

	float getX() const { return x; }
	float getY() const { return y; }

	void Move(const Player& player,float dt);        //跟踪玩家移动
	void takeDamage(int damage);

	void CheckPlayerAttack(Player& player);           //对玩家攻击检查
	bool CheckPlayerCollision(const Player& player);  //碰撞箱检测
	
	bool isAlive() const                              //检查Slime是否存活
	{ 
		return alive;
	}

	void setDeath();                                  //设置死亡

	void showSlime(float dt_ms);                      //动画处理
};

void printScore();                                    //左上角显示击杀数

#endif