#pragma once
#ifndef PLAYERANIME_H
#define PLAYERANIME_H
#include "animation.h"


extern Animation Knight_IdleL;
extern Animation Knight_IdleR;
extern Animation Knight_RunL;
extern Animation Knight_RunR;
extern Animation Knight_AttackSL;
extern Animation Knight_AttackSR;
extern Animation Knight_AttackHL;
extern Animation Knight_AttackHR;

void AnimeUpdate(Player* Player);

#endif