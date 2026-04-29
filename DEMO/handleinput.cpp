#include "handleinput.h"
#include "playeranime.h"
#include<cmath>

void handleInput(Player* Player)
{
	if (Player)
	{
		if (!Player->isHitting)
		{
			if (GetAsyncKeyState('A') & 0x8000)
			{
				Player->vx = -MOVE_SPEED;
				Player->isLeft = true;
			}
			else if (GetAsyncKeyState('D') & 0x8000)
			{
				Player->vx = MOVE_SPEED;
				Player->isLeft = false;
			}
			if (((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000)) && Player->isOnGround == true)
			{
				Player->vy = JUMP_SPEED;
				Player->isOnGround = false;
			}
			if ((GetAsyncKeyState('K') & 0x8000) && !Player->isAttackingS && Player->isOnGround == true)
			{
				Player->isHitting = true;
				Player->isAttackingS = true;
				Player->hitTimer = 0.63f;
				if (Player->isLeft)
				{
					Knight_AttackSL.resetAttack();
				}
				else
				{
					Knight_AttackSR.resetAttack();
				}
			}
			if ((GetAsyncKeyState('L') & 0x8000) && !Player->isAttackingH && Player->isOnGround == true)
			{
				Player->isHitting = true;
				Player->isAttackingH = true;
				Player->hitTimer = 1.08f;
				if (Player->isLeft)
				{
					Knight_AttackHL.resetAttack();
				}
				else
				{
					Knight_AttackHR.resetAttack();
				}
			}
			else
			{
				Player->vx *= 0.87f;         //减速
				if (abs(Player->vx) < 1.0f)
					Player->vx = 0;
			}
		}
	}
}
