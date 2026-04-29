#include<graphics.h>
#include"playeranime.h"

Animation Knight_IdleL(_T("img/Knight-IdleL%d.png"), 6, 120);
Animation Knight_IdleR(_T("img/Knight-IdleR%d.png"), 6, 120);
Animation Knight_RunL(_T("img/Knight-RunL%d.png"), 8, 45);
Animation Knight_RunR(_T("img/Knight-RunR%d.png"), 8, 45);
Animation Knight_AttackSL(_T("img/Knight-AttackSL%d.png"), 7, 90);
Animation Knight_AttackSR(_T("img/Knight-AttackSR%d.png"), 7, 90);
Animation Knight_AttackHL(_T("img/Knight-AttackHL%d.png"), 9, 120);
Animation Knight_AttackHR(_T("img/Knight-AttackHR%d.png"), 9, 120);

void AnimeUpdate(Player* Player)
{ 
	if (Player)
	{
		if (!Player->isHitting)
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
			if (Player->isLeft)
			{
				Knight_AttackHL.attackPlay((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
			else
			{
				Knight_AttackHR.attackPlay((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
		}
		else if (Player->isAttackingS)      //轻攻击
		{
			if (Player->isLeft)
			{
				Knight_AttackSL.attackPlay((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
			else
			{
				Knight_AttackSR.attackPlay((int)Player->getX(), (int)Player->getY(), delta_ms_copy);
			}
		}
	}
};