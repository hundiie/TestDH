// PCH
#pragma once

#include "Common.h"

// 씬 데이터 구조체
struct Scene_Data
{
    int SENCE_NUMBER;
    char IMG_NAME[128];
    char SOUND_NAME[128];
    char EFT_NAME[128];
    int EFT_STARTDEL;
    float EFT_TIME;
    int EFT_LOOP;
    char SENCE_STORY[2000];
    char CHOICE_STORY_1[128];
    int CHOICE_MOVE_1;
    char CHOICE_SOUND_1[128];
    char CHOICE_STORY_2[128];
    int CHOICE_MOVE_2;
    char CHOICE_SOUND_2[128];
    char CHOICE_STORY_3[128];
    int CHOICE_MOVE_3;
    char CHOICE_SOUND_3[128];
};

// 유저 구조체
struct User
{
    struct Scene_Data sceneData[200]; //200은 데이터 200줄 받음
};
struct User p1;

int CSV(void);