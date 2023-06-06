#pragma once
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

enum sounds
{
    checkMate,
    hit,
    knigtDeath,
    check,
    queenDeath,
    proneToQueen,
    hitCool,
    move,
    meow
};



void playSound(int op);


