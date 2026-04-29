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

void Animation::attackPlay(int x, int y, int delta)
{
	if (attackFinished)
	{
		return;
	}

	timer += delta;
	if (timer >= interval_ms)
	{
		timer = 0;
		if (idx_frame+1 < (int)frame_right.size())
		{
			idx_frame++;
		}
		if (idx_frame == (int)frame_right.size() - 1)
		{
			attackFinished = true;
		}
	}
	putimage_alpha(x, y, frame_right[idx_frame]);
}

void Animation::resetAttack()
{
	idx_frame = 0;
	timer = 0;
	attackFinished = false;
}

void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}    //去除黑边
