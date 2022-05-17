#include "stdafx.h"
#include "Scene.h"
#include "Text.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#define SOLID 0
#define SHADED 1
#define BLENDED 2

#pragma region TitleScene

#define TEXT_NUM_0 2
#define IMG_NUM_0 2
const wchar_t* title_str[] = {
	L"게임 시작",
	L"게임 종료"
};

typedef struct TitleSceneData
{
	Text	Choice[TEXT_NUM_0];
	Text	TitleText;
	COORD	coord;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage[IMG_NUM_0];
	int32		X;
	int32		Y;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->FontSize = 60;
	for (int32 i = 0; i < TEXT_NUM_0; ++i)
	{
		Text_CreateText(&data->Choice[i], "Chun_Bold.ttf", data->FontSize, title_str[i], wcslen(title_str[i]));
	}
	Text_CreateText(&data->TitleText, "Chun_Bold.ttf", data->FontSize, L"게임 제목", 5);
	data->RenderMode = SOLID;
	Image_LoadImage(&data->TestImage[0], "NamSan.jpg");
	Image_LoadImage(&data->TestImage[1], "Choice_2_Script.png");
	CSV;
}

int count = 0;
void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	if (count > 0)
	{
		if (Input_GetKeyDown(VK_LEFT))
		{
			count--;
		}
	}
	if (count < TEXT_NUM_0 - 1)
	{
		if (Input_GetKeyDown(VK_RIGHT))
		{
			count++;
		}
	}
	if (Input_GetKeyDown(VK_SPACE))
	{
		switch (count)
		{
		case 0:Scene_SetNextScene(SCENE_SCENE1);
			break;
		case 1:Scene_SetNextScene(SCENE_TITLE);
			break;
		}
		
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	data->X = 217;//선택지 시작 X좌표
	data->Y = 590;//선택지 시작 Y좌표
	int teem = 600;//석택지 사이의 거리

	SDL_Color color = { .r = 255, .g = 255, .b = 255 };//비 선택 색깔
	SDL_Color choice_color = { .g = 255 };//선택 색깔
	SDL_Color title_color = { .r = 200, .g =100, .b = 200 };//제목 색깔

	Renderer_DrawImage(&data->TestImage[0], 0, 0);

	Renderer_DrawImage(&data->TestImage[1], 0, 0);

	for (int i = 0; i < TEXT_NUM_0; i++)
	{	
		if (i != count)//선택 한 것 이외의 선택지 출력
		{
			Renderer_DrawTextSolid(&data->Choice[i], data->X+i*teem, data->Y, color);
		}
		if (i == count)
		{
			Renderer_DrawTextSolid(&data->Choice[count], data->X+ count * teem + count, data->Y + count, choice_color);//선택한 선택지 출력
		}
	}
	Renderer_DrawTextSolid(&data->TitleText, 500, 400, title_color);//제목 랜더링
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_0; ++i)
	{
		Text_FreeText(&data->Choice[i]);
	}

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region Scene1

#define CHOICE_TEXT_NUM_1 2//선택지 수
#define STORY_TEXT_NUM_1 4//스토리 문자열 수
#define IMG_NUM_1 4//이미지 수
#define FONT_SIZE_1 2//폰트 사이즈 수

const wchar_t* Scene1_story[] = {

	L"소스라치게 놀라며 눈을 뜨게 되었다.",
	L"눈을 뜨고 나니 앞에는 여자아이가 나에게 아빠라 부르고 있었다.",
	L"이 모든 상황이 어리둥절 하여 고개를 돌리며 주변을 둘러본다.",
	L"이 상황이 이해가 가지 않아 이곳이 어디인지 물어봐야겠다.",
};
const wchar_t* Scene1_choice[] = {

	L"지나가는 직원을 붙잡고 물어본다.",//씬 5이동
	L"앞에 있는 아이에게 물어본다.",//씬 4이동
};

typedef struct Senen1SceneData
{
	Text	ChoiceText[CHOICE_TEXT_NUM_1];
	Text	StoryText[STORY_TEXT_NUM_1];
	COORD	coord;
	int32	FontSize[FONT_SIZE_1];
	int32	RenderMode;
	Image	TestImage[IMG_NUM_1];
	int32		X;
	int32		Y;
} Senen1SceneData;

void init_scene1(void)
{
	g_Scene.Data = malloc(sizeof(Senen1SceneData));
	memset(g_Scene.Data, 0, sizeof(Senen1SceneData));

	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;

	data->FontSize[0] = 40;
	data->FontSize[1] = 30;
	
	for (int32 i = 0; i < STORY_TEXT_NUM_1; ++i)
	{
		Text_CreateText(&data->StoryText[i], "Chun_Bold.ttf", data->FontSize[0], Scene1_story[i], wcslen(Scene1_story[i]));
	}
	for (int32 i = 0; i < CHOICE_TEXT_NUM_1; ++i)
	{
		Text_CreateText(&data->ChoiceText[i], "Chun_Bold.ttf", data->FontSize[1], Scene1_choice[i], wcslen(Scene1_choice[i]));
	}

	Image_LoadImage(&data->TestImage[0], "1.png");
	Image_LoadImage(&data->TestImage[1], "No_Script.png");
	Image_LoadImage(&data->TestImage[2], "Choice_2_Script.png");
	Image_LoadImage(&data->TestImage[3], "3.png");
}

int count1 = 0;//대사를 한 줄 씩 출력하기 위한 카운터
int count1_2 = 0;//선택지 조절을 위한 카운터
void update_scene1(void)
{
	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE)&& count1 < STORY_TEXT_NUM_1)//Count1을 이용해서 텍스트를 한 줄 씩 만듬
	{
		count1++;
	}
	else//선택지로 이동
	{
		if (count1_2 > 0)
		{
			if (Input_GetKeyDown(VK_LEFT))
			{
				count1_2--;
			}
		}
		if (count1_2 < CHOICE_TEXT_NUM_1 - 1)
		{
			if (Input_GetKeyDown(VK_RIGHT))
			{
				count1_2++;
			}
		}
		if (Input_GetKeyDown(VK_SPACE))
		{
			switch (count1_2)
			{
			case 0:Scene_SetNextScene(SCENE_SCENE5);
				break;
			case 1:Scene_SetNextScene(SCENE_SCENE4);
				break;
			}
		}
	}
}
void render_scene1(void)
{
	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;

	data->X = 135;//선택지 시작 X좌표
	data->Y = 600;//선택지 시작 Y좌표
	int teem = 625;//석택지 사이의 거리

	SDL_Color color = { .r = 255, .g = 255, .b = 255 };//비 선택 색깔
	SDL_Color choice_color = { .g = 255 };//선택 색깔
	SDL_Color Stroy_color = { .r = 255, .g = 0, .b = 0 };//제목 색깔

	if (count1 < 3)
	{
		Renderer_DrawImage(&data->TestImage[0], 0, 0);
	}
	else
	{
		Renderer_DrawImage(&data->TestImage[3], 0, 0);
	}
	if (count1 <= STORY_TEXT_NUM_1 - 1)
	{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
		Renderer_DrawTextSolid(&data->StoryText[count1], 110, 500, Stroy_color);
	}
	else
	{
		Renderer_DrawImage(&data->TestImage[2], 0, 0);

		Renderer_DrawTextSolid(&data->StoryText[count1 - 1], 110, 450, Stroy_color);

		for (int i = 0; i < CHOICE_TEXT_NUM_1; i++)
		{
			if (i != count1_2)//선택 한 것 이외의 선택지 출력
			{
				Renderer_DrawTextSolid(&data->ChoiceText[i], data->X + i * teem, data->Y, color);
			}
			if (i == count1_2)
			{
				Renderer_DrawTextSolid(&data->ChoiceText[count1_2], data->X + count1_2 * teem, data->Y, choice_color);//선택한 선택지 출력
			}
		}
	}
}
	//}
	//if(count1 + 1 > STORY_TEXT_NUM_1)
	//{
	//	Renderer_DrawImage(&data->TestImage[2], 0, 0);

	//	for (int i = 0; i < CHOICE_TEXT_NUM_1; i++)
	//	{
	//		if (i != count1_2)//선택 한 것 이외의 선택지 출력
	//		{
	//			Renderer_DrawTextSolid(&data->ChoiceText[i], data->X + i * teem, data->Y, color);
	//		}
	//		if (i == count1_2)
	//		{
	//			Renderer_DrawTextSolid(&data->ChoiceText[count1_2], data->X + count1_2 * teem + count1_2, data->Y + count1_2, choice_color);//선택한 선택지 출력
	//		}
	//	}
	

void release_scene1(void)
{
	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;
	for (int32 i = 0; i < STORY_TEXT_NUM_1; ++i)
	{
		Text_FreeText(&data->StoryText[i]);
	}
	for (int32 i = 0; i < CHOICE_TEXT_NUM_1; ++i)
	{
		Text_FreeText(&data->ChoiceText[i]);
	}
	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region Scene2
void init_scene2(void)
{
}
void update_scene2(void)
{
}
void render_scene2(void)
{
}
void release_scene2(void)
{
}

#pragma endregion

#pragma region Scene3
void init_scene3(void)
{
}
void update_scene3(void)
{
}
void render_scene3(void)
{
}
void release_scene3(void)
{
}

#pragma endregion

#pragma region Scene4
void init_scene4(void)
{
}
void update_scene4(void)
{
}
void render_scene4(void)
{
}
void release_scene4(void)
{
}
#pragma endregion

#pragma region Scene5
void init_scene5(void)
{
}
void update_scene5(void)
{
}
void render_scene5(void)
{
}
void release_scene5(void)
{
}
#pragma endregion


//씬 함수
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
	case SCENE_SCENE1:
		g_Scene.Init = init_scene1;
		g_Scene.Update = update_scene1;
		g_Scene.Render = render_scene1;
		g_Scene.Release = release_scene1;
		break;
	case SCENE_SCENE2:
		g_Scene.Init = init_scene2;
		g_Scene.Update = update_scene2;
		g_Scene.Render = render_scene2;
		g_Scene.Release = release_scene2;
		break;
	case SCENE_SCENE3:
		g_Scene.Init = init_scene3;
		g_Scene.Update = update_scene3;
		g_Scene.Render = render_scene3;
		g_Scene.Release = release_scene3;
		break;
	case SCENE_SCENE4:
		g_Scene.Init = init_scene4;
		g_Scene.Update = update_scene4;
		g_Scene.Render = render_scene4;
		g_Scene.Release = release_scene4;
		break;
	case SCENE_SCENE5:
		g_Scene.Init = init_scene5;
		g_Scene.Update = update_scene5;
		g_Scene.Render = render_scene5;
		g_Scene.Release = release_scene5;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}