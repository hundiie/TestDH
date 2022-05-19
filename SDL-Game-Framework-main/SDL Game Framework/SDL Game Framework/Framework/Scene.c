#include "stdafx.h"
#include "Scene.h"
#include "Csv.h"
#include "Framework.h"
#include "CSV_farser.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;


#pragma region TitleScene

typedef struct TitleData
{
	//csv
	int32*	SCENE_NUMBER;	//1
	Text	STORY[10];		//2
	Text	CHOICE1;		//3
	int32	CHOICE1_MOVE;	//4
	Text	CHOICE1_SOUND;	//5
	Text	CHOICE2;		//6
	int32	CHOICE2_MOVE;	//7
	Text	CHOICE2_SOUND;	//8
	Text	CHOICE3;		//9
	int32	CHOICE3_MOVE;	//10
	Text	CHOICE3_SOUND;	//11
	Text	SOUND;			//12
	Text	IMAGE;			//13
	
} Titledata;

//ParseToUnicode(csvFile.Items[scene][2])//유니코드 (한글) 가져오기
//ParseToAscii(csvFile.Items[scene][2])//아스키 코드 (영어) 가져오기
//ParseToInt (csvFile.Items[scene][1])//정수 가져오기


void init_title(void)
{
	g_Scene.Data = malloc(sizeof(Titledata));
	memset(g_Scene.Data, 0, sizeof(Titledata));
	Titledata* data = (Titledata*)g_Scene.Data;
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	char* fname = "GGAM.csv";
	CreateCsvFile(&csvFile, fname);
	
	for (int i = 0; i < 10; i++)
	{
		wchar_t* str1[50] = { L"" };
		char *ttes = ParseToUnicode(csvFile.Items[1][2]);
		StringLine(ttes, str1);
		Text_CreateText(&data->STORY[i], "Chun_Bold.ttf", 20, str1, wcslen(str1));
	}

	//for (int32 i = 0; i < 10; ++i)
	//{
	//	//Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, ParseToAscii(csvFile.Items[1][2]), wcslen (ParseToAscii(csvFile.Items[1][2])));
	//}
	//StringLine(ParseToUnicode(csvFile.Items[1][2]),str1);
	//data->FontSize = 24;
	//Text_CreateText(&data->STORY, "Chun_Bold.ttf", 10, ParseToUnicode(csvFile.Items[scene][3]), wcslen (ParseToUnicode(csvFile.Items[scene][3])));

	Image_LoadImage(&data->IMAGE, ParseToAscii(csvFile.Items[1][13]));
	FreeCsvFile(&csvFile);

	
}

//choice(ParseToUnicode(csvFile.Items[scene][3], ParseToUnicode(csvFile.Items[scene][6], ParseToUnicode(csvFile.Items[scene][9])


void update_title(void)
{
	Titledata* data = (Titledata*)g_Scene.Data;
	
	//printf("%s", csv_t("GGAM.csv",1,2));

	//Text_SetFontStyle(&data->TestText, FS_ITALIC);
	
	if (Input_GetKeyDown(VK_SPACE))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	Titledata* data = (Titledata*)g_Scene.Data;
	SDL_Color color = { .r = 255, .g = 0, .b = 0 };//비 선택 색깔
	SDL_Color colora = { .r = 0, .g = 0, .b = 0 };//비 선택 색깔
	

	Renderer_DrawImage(&data->IMAGE, 0, 0);
	for (int i = 0; i < 6; i++)
	{
		Renderer_DrawTextBlended(&data->STORY[0], 100, 100+i*30,colora);
	}
	
}

void release_title(void)
{
	Titledata* data = (Titledata*)g_Scene.Data;

	//Text_FreeText(&data->STORY);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region MainScene

const wchar_t* str2[] = {""};

#define Stringline 10


typedef struct MainData
{
	//csv
	int32*	SCENE_NUMBER;		//1
	Text	STORY[Stringline];	//2
	Text	CHOICE1;			//3
	int32	CHOICE1_MOVE;		//4
	Text	CHOICE1_SOUND;		//5
	Text	CHOICE2;			//6
	int32	CHOICE2_MOVE;		//7
	Text	CHOICE2_SOUND;		//8
	Text	CHOICE3;			//9
	int32	CHOICE3_MOVE;		//10
	Text	CHOICE3_SOUND;		//11
	Text	SOUND;				//12
	Text	IMAGE;				//13

} MainSceneData;

//ParseToUnicode(csvFile.Items[scene][2])//유니코드 (한글) 가져오기
//ParseToAscii(csvFile.Items[scene][2])//아스키 코드 (영어) 가져오기
//ParseToInt (csvFile.Items[scene][1])//정수 가져오기

int scene = 1;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	char* fname = "GGAM.csv";
	CreateCsvFile(&csvFile, fname);
	
	for (int i = 0; i < Stringline; i++)
	{
		wchar_t* str1[50] = { L"" };
		char* ttes = ParseToUnicode(csvFile.Items[1][2]);
		StringLine(ttes, str1);

		Text_CreateText(&data->STORY[i], "Chun_Bold.ttf", 10, str1, wcslen(str1));
	}


}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	SafeFree(g_Scene.Data);
}
#pragma endregion


#pragma region END

void init_end(void)
{
}
void update_end (void)
{
}
void render_end (void)
{
}
void release_end (void)
{
}


#pragma endregion
bool Scene_IsSetNextScene(void)
{
	if (SCENE_NULL == s_nextScene)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Scene_SetNextScene(ESceneType scene)
{
	assert(s_nextScene == SCENE_NULL);
	assert(SCENE_NULL < scene&& scene < SCENE_MAX);

	s_nextScene = scene;
}

void Scene_Change(void)
{
	assert(s_nextScene != SCENE_NULL);

	if (g_Scene.Release)
	{
		g_Scene.Release();
	}

	switch (s_nextScene)
	{
	case SCENE_TITLE:
		g_Scene.Init = init_title;
		g_Scene.Update = update_title;
		g_Scene.Render = render_title;
		g_Scene.Release = release_title;
		break;
	case SCENE_MAIN:
		g_Scene.Init = init_main;
		g_Scene.Update = update_main;
		g_Scene.Render = render_main;
		g_Scene.Release = release_main;
		break;
	case SCENE_END:
		g_Scene.Init = init_end;
		g_Scene.Update = update_end;
		g_Scene.Render = render_end;
		g_Scene.Release = release_end;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}