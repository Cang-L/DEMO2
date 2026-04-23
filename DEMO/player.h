#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#include<graphics.h>

extern const float GROUND_Y;        //地面高度
extern const float GRAVITY;         //重力加速度(像素每二次方秒)
extern const float JUMP_SPEED;      //跳跃初速度(像素每秒)
extern const float MOVE_SPEED;      //水平移动速度

class Player 
{
	float x, y;    //坐标
	int hp=20;     //血量
	int height,wide;
public:
	bool isLeft;
	float getX() const { return x; }
	float getY() const { return y; }
	float vx, vy;  //速度
	Player(float x_0, float y_0);
	~Player() {}

	bool isOnGround = true;

	void PhyUpdate(float dt);
};

void handleInput(Player* Player);

#endif