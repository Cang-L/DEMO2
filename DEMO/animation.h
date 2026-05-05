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
	Animation(LPCTSTR path,int num,int interval);   //路径、图片数量、帧间隔
	~Animation();

	bool attackFinished = false;
	bool deathFinished = false;
	void Play(int x, int y, int delta);             
	void attackPlay(int x, int y, int delta);       //攻击动画播放
	void deathPlay(int x, int y, int delta);        //死亡动画播放
	void resetAttack();                             //攻击动画重置
	void resetDeath();                              //死亡动画重置
};

#endif