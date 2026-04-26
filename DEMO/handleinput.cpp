#include "handleinput.h"
#include<cmath>

void handleInput(Player* Player)
{
	if (Player)
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
		if (((GetAsyncKeyState('W') & 0x8000)|| (GetAsyncKeyState(VK_SPACE) & 0x8000))&& Player->isOnGround == true)
		{
			Player->vy = JUMP_SPEED;
			Player->isOnGround = false;
		}
		if ((GetAsyncKeyState('J') & 0x8000) && !Player->isAttackingS && Player->isOnGround == true)
		{
			Player->isAttackingS = true;
		}
		if ((GetAsyncKeyState('K') & 0x8000) && !Player->isAttackingH && Player->isOnGround == true)
		{
			Player->isAttackingH = true;
		}
		else
		{
			Player->vx *= 0.87f;         //减速
			if (abs(Player->vx) < 1.0f)
				Player->vx = 0;
		}
	}
}