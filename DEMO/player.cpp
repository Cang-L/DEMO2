#include<graphics.h>
#include<cmath>
#include"Player.h"
#pragma comment(lib,"dwmapi.lib")
const float GROUND_Y = 496;       //地面高度
const float GRAVITY = 1200.0;     //重力加速度(像素每二次方秒)
const float JUMP_SPEED = -450.0;  //跳跃初速度(像素每秒)
const float MOVE_SPEED = 250.0;   //水平移动速度

Player::Player(float x_0, float y_0) :x(x_0), y(y_0),vx(0),vy(0),height(32),width(32),isLeft(false),hitTimer(0){}

void Player::PhyUpdate(float dt) 
{
    vy += GRAVITY * dt;
	y += (vy * dt);
	x += (vx * dt);

	if (isHitting)
	{
		hitTimer -= dt;
		if (hitTimer <= 0)
		{
			isHitting = false;
			isAttackingS = false;
			isAttackingH = false;
		}
		vx = 0;
	}

	if (y >= GROUND_Y)
	{
		y = GROUND_Y;
		vy = 0;
		isOnGround = true;
	}
	if (x <= -48)
	{
		x = -48;
	}
	if (x + 96 >= 800)
	{
		x = 800 - 96;
	}
}
