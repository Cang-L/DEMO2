#pragma once
#ifndef SLIME_H
#define SLIME_H
#include "player.h"
#include "animation.h" 

extern Animation Slime_WalkL;
extern Animation Slime_WalkR;
extern Animation Slime_IDLER;
extern Animation Slime_IDLEL;

class Slime
{
private:
	float x, y;
	int hp = 2;
	const int SPEED = 100;
public:
	float vx;
	bool isLeft;

	Slime(float x_0, float y_0);

	float getX() const { return x; }
	float getY() const { return y; }

	void Move(const Player& player,Slime *pSlime, float dt);     //跟踪玩家移动

	bool CheckPlayerCollision(const Player& player)
	{
		return false;
	}

	void showSlime();
};

#endif