#pragma once
#ifndef SLIMECTRL_H
#define SLIMECTRL_H
#include "slime.h"

constexpr int MAX_SLIME = 20;       //变量初始化
extern Slime* pSlime[MAX_SLIME];
extern int slimecount;

extern float spawntimer;
extern float INTERVAL;

void spawnSlime(float dt);                          //周期添加Slime
void addSlime(float x, float y);                    //添加单只Slime
void updateSlime(const Player& player, float dt);   //所有Slime的Move操作
void removeDeadSlime();                             //移除death Slime
void drawSlime();                                   //所有Slime的showSlime操作
void clearSlime();                                  //清除所有Slime

#endif