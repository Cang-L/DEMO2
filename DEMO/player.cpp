#include<graphics.h>
#include<cmath>
#include"Player.h"
#pragma comment(lib,"dwmapi.lib")
const float GROUND_Y = 496;       //地面高度
const float GRAVITY = 1200.0;     //重力加速度(像素每二次方秒)
const float JUMP_SPEED = -450.0;  //跳跃初速度(像素每秒)
const float MOVE_SPEED = 250.0;   //水平移动速度

Player::Player(float x_0, float y_0) 
	:x(x_0)
	,y(y_0)
	,vx(0)
	,vy(0)
	,Height(128)
	,Width(128)
	,isLeft(false)
	,hitTimer(0)
    {}

void Player::PhyUpdate(float dt) 
{
    vy += GRAVITY * dt;
	y += (vy * dt);
	x += (vx * dt);

	if (checkAlive() && isHitting &&!getHurt)
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

	if (checkAlive() && getHurt)
	{
		float hurtSpeed = 20.0f;
		if (isLeft)
		{
			vx = hurtSpeed;
		}
		else if (isLeft)
		{
			vx = -hurtSpeed;
		}
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

bool Player::checkAlive()
{
	if (hp <= 0)
	{
		alive = false;
	}
	return alive;
}

void Player::takeDamage(int num)
{
	if (!alive)
	{
		return;
	}
	hp -= num;
	if (hp <= 0)
	{
		alive = false;
	}
	else 
	{
		getHurt = true;
	}
}