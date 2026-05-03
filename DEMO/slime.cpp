#include "slime.h"
#include <cmath>

Slime::Slime(float x_0, float y_0)
	:x(x_0)
	, y(y_0)
	, Width(128)
	, Height(128)
	, HitBoxW(64)
	, HitBoxH(16)
	, vx(0)
	, isLeft(true)
	, alive(true)
	, getHurt(false)
	, animeFinish(false)
	, Slime_WalkL(_T("img/Slime_walkL%d.png"), 4, 166)
	, Slime_WalkR(_T("img/Slime_walkR%d.png"), 4, 166)
	, Slime_IDLEL(_T("img/Slime_IDLEL%d.png"), 4, 166)
	, Slime_IDLER(_T("img/Slime_IDLER%d.png"), 4, 166)
	, Slime_DeathL(_T("img/Slime_DeathL%d.png"), 5, 200)
	, Slime_DeathR(_T("img/Slime_DeathR%d.png"), 5, 200)
    ,isAttacking(false)
	,hasAttacked(false)
    ,remainHurt(0.0f)
    ,attackDuration(0.25f)
    ,attackStart(0.0f)
    ,attackEnd(0.20f)
	,attackArea(100.0f)
    ,cooldownTimer(0.0f)
	,attackCooldown(2.0f)
	,attackTimer(0.0f)
    {}

void Slime::Move(const Player& player,float dt)
{
	const float& player_x = player.getX();
	float length = player_x - x;

	if (remainHurt > 0.0f)
	{
		remainHurt -= dt;
		if (remainHurt <= 0.0f)
		{
			remainHurt = 0;
			getHurt = false;
		}
		return;
	}

	if (!isAlive())
	{
		return;
	}

	if (isAttacking)
	{
		attackTimer += dt;
		float chargelen = player_x - x;
		if (chargelen > 0)
		{
			isLeft = false;
		}
		else
		{
			isLeft = true;
		}
		vx = (chargelen > 0) ? (float)chargeSpeed : -(float)chargeSpeed;
		float tempx = x + vx * dt;
		if ((isLeft && tempx < player.getX()) || (!isLeft && tempx > player.getX()))  //防止超过Player的位置
		{
			tempx = player.getX();
			isAttacking = false;
			cooldownTimer = attackCooldown;
			attackTimer = 0;
		}
		x = tempx;

		if (attackTimer >= attackDuration)
		{
			isAttacking = false;
			cooldownTimer = attackCooldown;
			attackTimer = 0;
		}
		return;
	}

	if (cooldownTimer > 0)
	{
		cooldownTimer -= dt;
	}

	if (length > 0)
	{
		isLeft = false;
	}
	else
	{
		isLeft = true;
	}

	if (fabs(length) < attackArea && cooldownTimer <= 0 && !isAttacking)
	{
		isAttacking = true;
		attackTimer = 0;
		return;
	}

	if (fabs(length) <= 400 && fabs(length) >= attackArea)
	{
		vx = (length > 0) ? (float)SPEED : -(float)SPEED;
	}
	else
	{
		vx = 0;
	}
	x += vx * dt;
	if (x <= -48)
	{
		x = -48;
		vx = 0;
	}
	if (x + 96 >= 800)
	{
		x = 800 - 96;
		vx = 0;
	}
}

void Slime::setDeath()
{
	alive = false;
}

void Slime::showSlime(float dt)
{
	if (isAlive())
	{
		if (vx != 0)
		{
			if (isLeft)
			{
				Slime_WalkL.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
			else if (!isLeft)
			{
				Slime_WalkR.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
		}
		else if (vx == 0)
		{
			if (isLeft)
			{
				Slime_IDLEL.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
			else if (!isLeft)
			{
				Slime_IDLER.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
		}
	}
	else if (!isAlive())
	{
		float INTERVAL = 1.0f;
		INTERVAL -= dt;
		if (INTERVAL > 0)
		{
			if (isLeft)
			{
				Slime_DeathL.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
			else if (!isLeft)
			{
				Slime_DeathR.Play((int)getX(), (int)getY(), delta_ms_copy);
			}
		}
		else if(INTERVAL <=0)
		{
			animeFinish = true;
			return;
		}
	}
}

void Slime::CheckPlayerAttack(Player& player)
{
	if (!isAttacking)
	{
		return;
	}
	if (isAttacking && attackTimer >= attackStart && attackTimer <= attackEnd && !hasAttacked)
	{
		if (CheckPlayerCollision(player))
		{
			player.takeDamage(1);
			hasAttacked = true;
		}
	}
}

bool Slime::CheckPlayerCollision(const Player& player)
{
	float pcx = player.getX() + player.Width / 2;   //player's central x 
	float pcy = player.getY() + player.Height / 2;  //player's central y
	float dir = 1;
	float scx = getX() + Width / 2;                 //slime's central x
	float scy = getY() + Height / 2;                //slime's central y
	if (isLeft)
	{
		if (scx - pcx >= 0 && scx - pcx <= HitBoxW && fabs(scy - pcy) <= HitBoxH)
		{
			return true;
		}
	}
	if (!isLeft)
	{
		if (pcx - scx >= 0 && pcx - scx <= HitBoxW && fabs(scy - pcy) <= HitBoxH)
		{
			return true;
		}
	}
	return false;
}

void Slime::takeDamage(int damage)
{
	if (!alive)
	{
		return;
	}
	hp -= damage;
	if (hp <= 0)
	{
		alive = false;
	}
	else
	{
		getHurt = true;
		remainHurt = 0.2f;
		if (isLeft)
		{
			x += 20.0f;
		}
		else
		{
			x -= 20.0f;
		}
	}
}