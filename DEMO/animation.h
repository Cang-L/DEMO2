#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include<graphics.h>
#include<vector>
#include "player.h"
extern int delta_ms_copy;

void putimage_alpha(int x, int y, IMAGE* img);

class Animation
{
private:
	int timer = 0;          //动画计时器
	int idx_frame = 0;      //动画帧索引
	int interval_ms = 0;    //帧间隔
	std::vector<IMAGE*> frame_right;

public:
	Animation(LPCTSTR path,int num,int interval);  //路径、图片数量、帧间隔
	~Animation();
	void Play(int x, int y, int delta);
};

void AnimeUpdate(Player* Player);
#endif