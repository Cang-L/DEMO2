#include<graphics.h>
#include"playeranime.h"

Animation Knight_IdleL(_T("img/Knight-IdleL%d.png"), 6, 120);
Animation Knight_IdleR(_T("img/Knight-IdleR%d.png"), 6, 120);
Animation Knight_RunL(_T("img/Knight-RunL%d.png"), 8, 45);
Animation Knight_RunR(_T("img/Knight-RunR%d.png"), 8, 45);
void AnimeUpdate(Player* Player)
{
	if (Player)
	{
		if ((!Player->isAttackingH)&&(!Player->isAttackingS))
		{
			if (Player->isLeft && (abs(Player->vx) <= 20.0f || Player->isOnGround == false))
			{
				Knight_IdleL.Play((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
			else if (Player->isLeft == false && (abs(Player->vx) <= 20.0f || Player->isOnGround == false))
			{
				Knight_IdleR.Play((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
			else if (Player->isLeft && (abs(Player->vx) > 20.0f && Player->isOnGround == true))
			{
				Knight_RunL.Play((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
			else if (Player->isLeft == false && (abs(Player->vx) > 20.0f && Player->isOnGround == true))
			{
				Knight_RunR.Play((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
		}
		else if (Player->isAttackingH)      //重攻击
		{
		}
		else if (Player->isAttackingS)      //轻攻击
		{
		}
	}
};