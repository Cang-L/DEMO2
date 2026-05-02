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

	float x, y;
	int hp = 2;
	const int SPEED = 100;

public:
	float vx;
	bool isLeft;
	bool alive;

	Slime(float x_0, float y_0);

	float getX() const { return x; }
	float getY() const { return y; }

	void Move(const Player& player,float dt);        //跟踪玩家移动

	bool CheckPlayerCollision(const Player& player)  //碰撞箱设置
	{
		return false;
	}

	bool isAlive() const                             //检查是否存活
	{
		return alive;
	}

	void setDeath();

	void showSlime();
};

#endif