#include "slime.h"
#include <cmath>

Animation Slime_WalkL(_T("img/Slime_walkL%d.png"), 4, 166);
Animation Slime_WalkR(_T("img/Slime_walkR%d.png"), 4, 166);
Animation Slime_IDLEL(_T("img/Slime_IDLEL%d.png"), 4, 166);
Animation Slime_IDLER(_T("img/Slime_IDLER%d.png"), 4, 166);

Slime::Slime(float x_0,float y_0):x(x_0),y(GROUND_Y), vx(0),isLeft(true){};

void Slime::Move(const Player& player, Slime *pSlime, float dt)
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
	if (abs(length) <= 300 && abs(length)>=40)
	{
		pSlime->vx = (float)SPEED;
		if (length > 0)
		{
			x += vx * dt;
		}
		else if (length < 0)
		{
			vx = -(float)SPEED;
			x += vx * dt;
		}
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
