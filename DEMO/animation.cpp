#include "animation.h"
#include <windows.h>
#include <tchar.h>
#include<string>
#include<cmath>
#pragma comment(lib, "msimg32.lib") 

int delta_ms_copy=0;

Animation::Animation(LPCTSTR path, int num, int interval) 
{
	interval_ms = interval;
	timer = 0;
	idx_frame = 0;
	TCHAR path_file[256];
	for (size_t i = 0; i < num; i++)
	{
		_stprintf_s(path_file, path, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_right.push_back(frame);
	}
}

Animation::~Animation()
{
	for (size_t i = 0; i < frame_right.size(); i++)
	{
		delete frame_right[i];
	}
}

void Animation::Play(int x, int y, int delta) 
{
	timer += delta;
	if (timer >= interval_ms)
	{
		idx_frame = (idx_frame + 1) % frame_right.size();
		timer = 0;
	}
	putimage_alpha(x, y, frame_right[idx_frame]);
}

void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}//去除黑边

Animation Knight_IdleL(_T("img/Knight-IdleL%d.png"), 6, 120);
Animation Knight_IdleR(_T("img/Knight-IdleR%d.png"), 6, 120);
Animation Knight_RunL(_T("img/Knight-RunL%d.png"), 8, 45);
Animation Knight_RunR(_T("img/Knight-RunR%d.png"), 8, 45);
void AnimeUpdate(Player* Player)
{
	if (Player)
	{
		if (Player->isLeft && (abs(Player->vx) <= 20.0f ||Player->isOnGround==false))
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
}