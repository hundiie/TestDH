#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char one_line_string[1000];

int CSV()
{
    FILE* p_file;

    if (0 == fopen_s(&p_file, "asdver.1.csv", "rt"))//파일 이름 넣기
    {

        //맨 처음 줄 넘기기
        if (NULL != fgets(one_line_string, 1000, p_file)) {
            memset(one_line_string, 0, sizeof(one_line_string));
        }

        int count = 0;

        while (fscanf(p_file, "%[^\n] ", one_line_string) != EOF) {
            char* ptr = strtok(one_line_string, ",");
            int count2 = 0;

            while (ptr != NULL)               // 자른 문자열이 나오지 않을 때까지 반복
            {
                if (count2 == 0) {
                    p1.sceneData[count].SENCE_NUMBER = atoi(ptr);
                }
                else if (count2 == 1) {
                    strcpy(p1.sceneData[count].IMG_NAME, ptr);
                }
                else if (count2 == 2) {
                    strcpy(p1.sceneData[count].SOUND_NAME, ptr);
                }
                else if (count2 == 3) {
                    strcpy(p1.sceneData[count].EFT_NAME, ptr);
                }
                else if (count2 == 4) {
                    p1.sceneData[count].EFT_STARTDEL = atoi(ptr);
                }
                else if (count2 == 5) {
                    p1.sceneData[count].EFT_TIME = atoi(ptr);
                }
                else if (count2 == 6) {
                    p1.sceneData[count].EFT_LOOP = atoi(ptr);
                }
                else if (count2 == 7) {
                    strcpy(p1.sceneData[count].SENCE_STORY, ptr);
                }
                else if (count2 == 8) {
                    strcpy(p1.sceneData[count].CHOICE_STORY_1, ptr);
                }
                else if (count2 == 9) {
                    p1.sceneData[count].CHOICE_MOVE_1 = atoi(ptr);
                }
                else if (count2 == 10) {
                    strcpy(p1.sceneData[count].CHOICE_SOUND_1, ptr);
                }
                else if (count2 == 11) {
                    strcpy(p1.sceneData[count].CHOICE_STORY_2, ptr);
                }
                else if (count2 == 12) {
                    p1.sceneData[count].CHOICE_MOVE_2 = atoi(ptr);
                }
                else if (count2 == 13) {
                    strcpy(p1.sceneData[count].CHOICE_SOUND_2, ptr);
                }
                else if (count2 == 14) {
                    strcpy(p1.sceneData[count].CHOICE_STORY_3, ptr);
                }
                else if (count2 == 15) {
                    p1.sceneData[count].CHOICE_MOVE_3 = atoi(ptr);
                }
                else if (count2 == 16) {
                    strcpy(p1.sceneData[count].CHOICE_SOUND_3, ptr);
                }

                count2++;
                ptr = strtok(NULL, ",");      // 다음 문자열을 잘라서 포인터를 반환
            }
            count++;
            memset(one_line_string, 0, sizeof(one_line_string));
        }
    }

    fclose(p_file);

    printf("%d\n", p1.sceneData[0].SENCE_NUMBER);
    printf("%s\n", p1.sceneData[0].IMG_NAME);
    printf("%s\n", p1.sceneData[0].SOUND_NAME);
    printf("%s\n", p1.sceneData[0].EFT_NAME);
    printf("%d\n", p1.sceneData[0].EFT_STARTDEL);
    printf("%f\n", p1.sceneData[0].EFT_TIME);
    printf("%d\n", p1.sceneData[0].EFT_LOOP);
    printf("%s\n", p1.sceneData[0].SENCE_STORY);
    printf("%s\n", p1.sceneData[0].CHOICE_STORY_1);
    printf("%d\n", p1.sceneData[0].CHOICE_MOVE_1);
    printf("%s\n", p1.sceneData[0].CHOICE_SOUND_1);
    printf("%s\n", p1.sceneData[0].CHOICE_STORY_2);
    printf("%d\n", p1.sceneData[0].CHOICE_MOVE_2);
    printf("%s\n", p1.sceneData[0].CHOICE_SOUND_2);
    printf("%s\n", p1.sceneData[0].CHOICE_STORY_3);
    printf("%d\n", p1.sceneData[0].CHOICE_MOVE_3);
    printf("%s\n", p1.sceneData[0].CHOICE_SOUND_3);
}