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
	,HitBoxW(80)
	,HitBoxH(16)
	,isLeft(false)
	,hitDurationS(0.63f)
	,hitDurationH(1.08f)
	,invincibleTimer(-1.0f)
	,HurtTime(0.0f)
	,attackTimerH(0.0f)
	,attackStartH(0.72f)
	,attackEndH(1.08f)
	,attackTimerS(0.0f)
	,attackStartS(0.18f)
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
		onDeath();
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
	if (getHurt)
	{
		return;
	}
	if (!isAttackingH&&!isAttackingS)
	{
		return;
	}
	if (isAttackingH && attackTimerH >= attackStartH && attackTimerH <= attackEndH)
	{
		if (!hasHit && checkSlimeCollision(slime))
		{
			slime.takeDamage(2, (slime.getX() > getX()) ? 1.0f : -1.0f);
			hasHit = true;
		}
	}
	if (isAttackingS && attackTimerS >= attackStartS && attackTimerS <= attackEndS)
	{
		if (!hasHit && checkSlimeCollision(slime))
		{
			slime.takeDamage(1,(slime.getX()>getX())?1.0f:-1.0f);
			hasHit = true;
		}
	}
}
bool Player::checkSlimeCollision(const Slime& slime) 
{
	float scx = slime.getX() + slime.Width / 2;   //slime's central x 
	float scy = slime.getY() + slime.Height / 2;  //slime's central y
	float pcx = getX() + Width / 2;               //player's central x
	float pcy = getY() + Height / 2;              //player's central y
	if (isLeft)
	{

		if (pcx - scx >= 0 && pcx - scx <= HitBoxW && fabs(pcy - scy) <= HitBoxH)
		{
			return true;
		}
	}
	if (!isLeft)
	{
		if (scx - pcx >= 0 && scx - pcx <= HitBoxW && fabs(scy - pcy) <= HitBoxH)
		{
			return true;
		}
	}
	return false;
}

void Player::onDeath()
{
	alive = false;
	if (isLeft)
	{
		Knight_DeathL.resetDeath();
	}
	else
	{
		Knight_DeathR.resetDeath();
	}
}