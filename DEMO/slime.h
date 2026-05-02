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

	Slime(float x_0, float y_0);

	float getX() const { return x; }
	float getY() const { return y; }

	void Move(const Player& player,float dt);     //跟踪玩家移动

	bool CheckPlayerCollision(const Player& player)
	{
		return false;
	}

	void showSlime();
};

extern std::vector<std::unique_ptr<Slime>>slime;
void updateSlime(float dt);
#endif