#include "handleinput.h"
#include "playeranime.h"
#include<cmath>

void handleInput(Player* Player)
{
	if (!Player)return;
	if (!Player->isAlive() || Player->getHurt) return;

	bool left = (GetAsyncKeyState('A') & 0x8000);
	bool right = (GetAsyncKeyState('D') & 0x8000);
	if (left && !right)
	{
		Player->vx = -MOVE_SPEED;
		Player->isLeft = true;
	}
	else if (right && !left)
	{
		Player->vx = MOVE_SPEED;
		Player->isLeft = false;
	}
	else
	{
		Player->vx *= 0.87f;         //减速
		if (abs(Player->vx) < 1.0f)
			Player->vx = 0;
	}

	if (((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState(VK_SPACE) & 0x8000)) && Player->isOnGround)
	{
		Player->vy = JUMP_SPEED;
		Player->isOnGround = false;
	}

	if ((GetAsyncKeyState('K') & 0x8000) && !Player->isAttackingS && Player->isOnGround)
	{
		Player->isAttackingS = true;
		Player->hasHit = false;
		Player->attackTimerS = 0.0f;
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
		Player->isAttackingH = true;
		Player->hasHit = false;
		Player->attackTimerH = 0;
		if (Player->isLeft)
		{
			Knight_AttackHL.resetAttack();
		}
		else
		{
			Knight_AttackHR.resetAttack();
		}
	}
}
