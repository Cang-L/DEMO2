#include "slimectrl.h"

float spawntimer = 0.0f;
float INTERVAL = 2.0f;

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

void updateSlime(const Player& player, float dt)
{
	for (int i = 0; i < slimecount; ++i)
	{
		if (pSlime[i]->isAlive())
		{
			pSlime[i]->Move(player,dt);
		}
	}
}

void removeDeadSlime()
{
	int i = 0;
	while (i < slimecount)
	{
		if (!pSlime[i]->isAlive())
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
		pSlime[i]->showSlime();
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