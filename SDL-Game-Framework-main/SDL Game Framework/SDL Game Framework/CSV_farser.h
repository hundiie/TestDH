#pragma once
#include "Common.h"
#include "stdafx.h"
#include "Framework/Text.h"

typedef enum mainGame
{
	SCENE_NUMBER = 1,
	STORY,
	CHOICE1,
	CHOICE1_MOVE,
	CHOICE1_SOUND,
	CHOICE2,
	CHOICE2_MOVE,
	CHOICE2_SOUND,
	CHOICE3,
	CHOICE3_MOVE,
	CHOICE3_SOUND,
	SOUND,
	IMAGE
}MAINGAME;


void* csv_t(char* fileName, int x, int y);

