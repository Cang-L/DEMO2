#include<graphics.h>
#include<cmath>
#include "Player.h"
#include "Playeranime.h"
#include "slime.h"
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
	,HitBoxW(64)
	,HitBoxH(16)
	,isLeft(false)
	,hitDurationS(0.63f)
	,hitDurationH(1.08f)
	,invincibleTimer(-1.0f)
	,HurtTime(-1.0f)
	,attackTimerH(-1.0)
	,attackStartH(0.24f)
	,attackEndH(0.96f)
	,attackTimerS(-1.0)
	,attackStartS(0.0f)
	,attackEndS(0.54f)
    {}

void Player::PhyUpdate(float dt) 
{
	vy += GRAVITY * dt;

	if (invincibleTimer > 0)
	{
		invincibleTimer -= dt;
		if (invincibleTimer <= 0)
		{
			invincible = false;
			invincibleTimer = 0;
		}
	}

	if (HurtTime >= 0)
	{
		HurtTime -= dt;
		if (HurtTime <= 0)
		{
			getHurt = false;
			HurtTime = 0;
		}
	}

	if (!isAlive())
	{
		return;
	}

	if (isAlive() && (isAttackingS || isAttackingH) && !getHurt)
	{
		vx = 0;
	}
	y += vy * dt;
	x += vx * dt;

	if (isAlive() && getHurt && HurtTime > 0)
	{
		float hurtSpeed = 20.0f;
        if (isLeft)
		{
			vx = hurtSpeed;
		}
		else if (!isLeft)
		{
			vx = -hurtSpeed;
		}
		x += vx * dt;
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

	if (isAlive() && isAttackingS && !getHurt)
	{
		attackTimerS += dt;
		if (attackTimerS>=hitDurationS)
		{
			isAttackingS = false;
			attackTimerS = 0;
		}
	}

	if (isAlive() && isAttackingH && !getHurt)
	{
		attackTimerH += dt;
		if (attackTimerH>=hitDurationH)
		{
			isAttackingH = false;
			attackTimerH = 0;
		}
	}
}

bool Player::isAlive()
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
	if (invincible)
	{
		return;
	}
	hp -= num;
	if (hp <= 0)
	{
		alive = false;
		return;
	}

    getHurt = true;
	invincible = true;
	invincibleTimer = 0.8f;
	HurtTime = 0.3f;

	isAttackingS = false;
	isAttackingH = false;
	attackTimerS = 0;
	attackTimerH = 0;

	if (isLeft)
	{
		Knight_HurtL.resetAttack();
	}
	else
	{
		Knight_HurtR.resetAttack();
	}
}

void Player::checkSlimeAttack(Slime& slime)
{
	if (!isAttackingH&&!isAttackingS)
	{
		return;
	}
	if (isAttackingH && attackTimerH >= attackStartH && attackTimerH <= attackEndH)
	{
		if (checkSlimeCollision(slime))
		{
			slime.takeDamage(2);
		}
	}
	if (isAttackingS && attackTimerS >= attackStartS && attackTimerS <= attackEndS)
	{
		if (checkSlimeCollision(slime))
		{
			slime.takeDamage(1);
		}
	}
}
bool Player::checkSlimeCollision(const Slime& slime) 
{
	float pcx = slime.getX() + slime.Width / 2;   //player's central x 
	float pcy = slime.getY() + slime.Height / 2;  //player's central y
	float scx = getX() + Width / 2;               //slime's central x
	float scy = getY() + Height / 2;              //slime's central y
	if (isLeft)
	{

		if (pcx - scx >= 0 && pcx - scx <= HitBoxW && fabs(pcy - scy) <= HitBoxH)
		{
			return true;
		}
	}
	if (!isLeft)
	{
		if (scx - pcx >= 0 && scx - pcx <= HitBoxW && fabs(scx - pcx) <= HitBoxH)
		{
			return true;
		}
	}
	return false;
}