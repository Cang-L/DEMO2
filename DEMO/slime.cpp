#include "slime.h"
#include <cmath>

Animation Slime_WalkL(_T("img/Slime_walkL%d.png"), 4, 120);
Animation Slime_WalkR(_T("img/Slime_walkR%d.png"), 4, 120);
Animation Slime_IDLEL(_T("img/Slime_IDLEL%d.png"), 4, 120);
Animation Slime_IDLER(_T("img/Slime_IDLER%d.png"), 4, 120);

Slime::Slime(float x_0,float y_0):x(x_0),y(GROUND_Y), vx(0),isLeft(true){};

void Slime::Move(const Player& player, Slime *pSlime, float dt)
{
	const float& player_x = player.getX();
	float length = player_x - x;

	if (abs(length) <= 300 && abs(length)>=40)
	{
		pSlime->vx = (float)SPEED;
		if (length > 0)
		{
			isLeft = false;
			x += vx * dt;
		}
		else if (length < 0)
		{
			isLeft = true;
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

void Slime::showSlime(Slime* pSlime)
{
	if (pSlime->vx != 0)
	{
		if (pSlime->isLeft)
		{
			Slime_WalkL.Play((int)pSlime->getX(), (int)pSlime->getY(), delta_ms_copy);
		}
		else if (!pSlime->isLeft)
		{
			Slime_WalkR.Play((int)pSlime->getX(), (int)pSlime->getY(), delta_ms_copy);
		}
	}
	else if (pSlime->vx == 0)
	{
		if (pSlime->isLeft)
		{
			Slime_IDLEL.Play((int)pSlime->getX(), (int)pSlime->getY(), delta_ms_copy);
		}
		else if (!pSlime->isLeft)
		{
			Slime_IDLER.Play((int)pSlime->getX(), (int)pSlime->getY(), delta_ms_copy);
		}
	}
}