#include "slime.h"
#include <cmath>

Slime::Slime(float x_0,float y_0):x(x_0),y(y_0), vx(0),isLeft(true),alive(true),Slime_WalkL(_T("img/Slime_walkL%d.png"), 4, 166), Slime_WalkR(_T("img/Slime_walkR%d.png"), 4, 166) , Slime_IDLEL(_T("img/Slime_IDLEL%d.png"), 4, 166) , Slime_IDLER(_T("img/Slime_IDLER%d.png"), 4, 166) {};

void Slime::Move(const Player& player,float dt)
{
	const float& player_x = player.getX();
	float length = player_x - x;

	if (length > 0)
	{
		isLeft = false;
	}
	else
	{
		isLeft = true;
	}
	if (fabs(length) <= 300 && fabs(length)>=40)
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

void Slime::showSlime()
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
