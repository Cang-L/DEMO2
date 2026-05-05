#include "slimectrl.h"

float spawntimer = 0.0f;
float INTERVAL = 3.0f;

Slime* pSlime[MAX_SLIME];
int slimecount = 0;

void addSlime(float x, float y)
{
	if (slimecount >= MAX_SLIME)
	{
		return;
	}
	pSlime[slimecount++] = new Slime(x, y);
}

void updateSlime(Player& player, float dt)
{
	for (int i = 0; i < slimecount; ++i)
	{
		if (pSlime[i]->isAlive() && pSlime[i] != nullptr)
		{
			pSlime[i]->Move(player,dt);
			pSlime[i]->CheckPlayerAttack(player);
			player.checkSlimeAttack(*pSlime[i]);
		}
	}
}

void removeDeadSlime()
{
	int i = 0;
	while (i < slimecount)
	{
		if (!pSlime[i]->isAlive() && pSlime[i]->animeFinish)
		{
			delete pSlime[i];
			pSlime[i] = pSlime[slimecount - 1];
			slimecount--;
		}
		else 
		{
			i++;
		}
	}
}

void drawSlime()
{
	for (int i = 0; i < slimecount; ++i) 
	{
		pSlime[i]->showSlime((float)delta_ms_copy);
	}
}

void clearSlime()
{
	for (int i = 0; i < slimecount; ++i)
	{
		delete pSlime[i];
	}
	slimecount = 0;
}

void spawnSlime(float dt)
{
	spawntimer += dt;
	if (spawntimer >= INTERVAL)
	{
		spawntimer = 0;
		addSlime(700, GROUND_Y);
	}
}