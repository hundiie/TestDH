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
	L"���� ����",
	L"���� ����"
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
	Text_CreateText(&data->TitleText, "Chun_Bold.ttf", data->FontSize, L"���� ����", 5);
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
	
	data->X = 217;//������ ���� X��ǥ
	data->Y = 590;//������ ���� Y��ǥ
	int teem = 600;//������ ������ �Ÿ�

	SDL_Color color = { .r = 255, .g = 255, .b = 255 };//�� ���� ����
	SDL_Color choice_color = { .g = 255 };//���� ����
	SDL_Color title_color = { .r = 200, .g =100, .b = 200 };//���� ����

	Renderer_DrawImage(&data->TestImage[0], 0, 0);

	Renderer_DrawImage(&data->TestImage[1], 0, 0);

	for (int i = 0; i < TEXT_NUM_0; i++)
	{	
		if (i != count)//���� �� �� �̿��� ������ ���
		{
			Renderer_DrawTextSolid(&data->Choice[i], data->X+i*teem, data->Y, color);
		}
		if (i == count)
		{
			Renderer_DrawTextSolid(&data->Choice[count], data->X+ count * teem + count, data->Y + count, choice_color);//������ ������ ���
		}
	}
	Renderer_DrawTextSolid(&data->TitleText, 500, 400, title_color);//���� ������
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

#define CHOICE_TEXT_NUM_1 2//������ ��
#define STORY_TEXT_NUM_1 4//���丮 ���ڿ� ��
#define IMG_NUM_1 4//�̹��� ��
#define FONT_SIZE_1 2//��Ʈ ������ ��

const wchar_t* Scene1_story[] = {

	L"�ҽ���ġ�� ���� ���� �߰� �Ǿ���.",
	L"���� �߰� ���� �տ��� ���ھ��̰� ������ �ƺ��� �θ��� �־���.",
	L"�� ��� ��Ȳ�� ����� �Ͽ� ���� ������ �ֺ��� �ѷ�����.",
	L"�� ��Ȳ�� ���ذ� ���� �ʾ� �̰��� ������� ������߰ڴ�.",
};
const wchar_t* Scene1_choice[] = {

	L"�������� ������ ����� �����.",//�� 5�̵�
	L"�տ� �ִ� ���̿��� �����.",//�� 4�̵�
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

int count1 = 0;//��縦 �� �� �� ����ϱ� ���� ī����
int count1_2 = 0;//������ ������ ���� ī����
void update_scene1(void)
{
	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE)&& count1 < STORY_TEXT_NUM_1)//Count1�� �̿��ؼ� �ؽ�Ʈ�� �� �� �� ����
	{
		count1++;
	}
	else//�������� �̵�
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
			case 0:Scene_SetNextScene(SCENE_SCENE2);
				count1_2 = 3;
				break;
			case 1:Scene_SetNextScene(SCENE_SCENE2);
				count1_2 = 0;
				break;
			}
		}
	}
}
void render_scene1(void)
{
	Senen1SceneData* data = (Senen1SceneData*)g_Scene.Data;

	data->X = 135;//������ ���� X��ǥ
	data->Y = 600;//������ ���� Y��ǥ
	int teem = 625;//������ ������ �Ÿ�

	SDL_Color color = { .r = 255, .g = 255, .b = 255 };//�� ���� ����
	SDL_Color choice_color = { .g = 255 };//���� ����
	SDL_Color Stroy_color = { .r = 255, .g = 0, .b = 0 };//���� ����

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
			if (i != count1_2)//���� �� �� �̿��� ������ ���
			{
				Renderer_DrawTextSolid(&data->ChoiceText[i], data->X + i * teem, data->Y, color);
			}
			if (i == count1_2)
			{
				Renderer_DrawTextSolid(&data->ChoiceText[count1_2], data->X + count1_2 * teem, data->Y, choice_color);//������ ������ ���
			}
		}
	}
}

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

#define CHOICE_TEXT_NUM_2 6//������ ��
#define STORY_TEXT_NUM_2 10//���丮 ���ڿ� ��
#define IMG_NUM_2 5//�̹��� ��
#define FONT_SIZE_2 2//��Ʈ ������ ��

const wchar_t* Scene2_story[] = {
	L"���� �ƺ��� ������ ����شٰ� ����ؼ� ���ݾ�!",//���̼���
	L"�� ���� ����Ÿ�� ������ �Դϴ�.",
	L"����Ÿ���� �� 7������ �����Ǿ��ֽ��ϴ�.",
	L"1������ ���� ����Ʈ��, 2������ �׶�, 3�����¡�",//���� ����
	L"���� 31��� Ư���δ� �������̶�� ��ǰ� �����������̶��",
	L"��Ǹ� �Ӹ��ӿ� �ɵ��� �� ��Ȳ�� ���ص��� �ʴ´�.",
	L"�� �տ� �ִ� ���̴� �������� ���͵��� �� �� ���� �ǹ� �����̴�.",
	L"������ ������ ũ�� ������ �����ʾҴ�.",//����
	L"�������� ��������͸����δ� ������ �����ϴ�.",
	L"�ֺ��� �����Ͽ� �� �� ������ �����ؾ� �� �ʿ䰡 ������ ����."
};
const wchar_t* Scene2_choice[] = {
	L"���̿��� ����� �Ǽ��ΰŰ���.",
	L"�������� �����",
	L"(�ڽ��� �Ӹ��� �ο�������)",
	L"������ ����ϴ�.",
	L"���ź��� ������������, ȭ��ǿ� ���� ������ ����",
	L"���ڿ� ������ �ִ� �Ź��� Ȯ���Ѵ�."
};

typedef struct Senen2SceneData
{
	Text	ChoiceText[CHOICE_TEXT_NUM_2];
	Text	StoryText[STORY_TEXT_NUM_2];
	COORD	coord;
	int32	FontSize[FONT_SIZE_2];
	int32	RenderMode;
	Image	TestImage[IMG_NUM_2];
	int32	X;
	int32	Y;
	int32	Count;
} Senen2SceneData;

void init_scene2(void)
{
	
	g_Scene.Data = malloc(sizeof(Senen2SceneData));
	memset(g_Scene.Data, 0, sizeof(Senen2SceneData));

	Senen2SceneData* data = (Senen2SceneData*)g_Scene.Data;
	
	data->Count = count1_2;
	data->FontSize[0] = 40;
	data->FontSize[1] = 30;

	for (int32 i = 0; i < STORY_TEXT_NUM_2; ++i)
	{
		Text_CreateText(&data->StoryText[i], "Chun_Bold.ttf", data->FontSize[0], Scene2_story[i], wcslen(Scene2_story[i]));
	}
	for (int32 i = 0; i < CHOICE_TEXT_NUM_2; ++i)
	{
		Text_CreateText(&data->ChoiceText[i], "Chun_Bold.ttf", data->FontSize[1], Scene2_choice[i], wcslen(Scene2_choice[i]));
	}
	for (int32 i = 4; i < CHOICE_TEXT_NUM_2; ++i)
	{
		Text_CreateText(&data->ChoiceText[i], "Chun_Bold.ttf", 20, Scene2_choice[i], wcslen(Scene2_choice[i]));
	}
	Image_LoadImage(&data->TestImage[0], "4.png");
	Image_LoadImage(&data->TestImage[1], "No_Script.png");
	Image_LoadImage(&data->TestImage[2], "Choice_1_Script.png");
	Image_LoadImage(&data->TestImage[3], "5.png");
	Image_LoadImage(&data->TestImage[4], "Choice_2_Script.png");
}
int count2=0;
void update_scene2(void)
{
	Senen2SceneData* data = (Senen2SceneData*)g_Scene.Data;

	if (Input_GetKeyDown(VK_SPACE)&& (data->Count < 14))
	{
		data->Count++;
		//Scene_SetNextScene(SCENE_SCENE3);
	}
	else
	{
		if (count2 > 0)
		{
			if (Input_GetKeyDown(VK_LEFT))
			{
				count2--;
			}
		}
		if (count2 < 2)
		{
			if (Input_GetKeyDown(VK_RIGHT))
			{
				count2++;
			}
		}
		if (Input_GetKeyDown(VK_SPACE))
		{
			switch (count2)
			{
			case 0:Scene_SetNextScene(SCENE_SCENE3);
				count2 = 0;
				break;
			case 1:Scene_SetNextScene(SCENE_SCENE3);
				count2 = 1;
				break;
			}
		}
	}
}
void render_scene2(void)
{
	Senen2SceneData* data = (Senen2SceneData*)g_Scene.Data;
	
	data->X = 130;//������ ���� X��ǥ
	data->Y = 600;//������ ���� Y��ǥ
	int teem = 610;//������ ������ �Ÿ�

	SDL_Color color = { .r = 255, .g = 255, .b = 255 };//�� ���� ����
	SDL_Color choice_color = { .g = 255 };//���� ����
	SDL_Color Stroy_color = { .r = 255, .g = 0, .b = 0 };//���� ����
#pragma region Hard_coding
	if (data->Count < 3)
	{
		Renderer_DrawImage(&data->TestImage[0], 0, 0);   //¥������ �ϵ��ڵ���
		if (data->Count == 0)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[0], 90, 500, Stroy_color);
		}
		else		{
			Renderer_DrawImage(&data->TestImage[2], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[0], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->ChoiceText[data->Count - 1], data->X, data->Y, choice_color);
		}
	}
	else  if (data->Count < 8)
	{
		Renderer_DrawImage(&data->TestImage[3], 0, 0);
		if (data->Count < 6)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			if (data->Count ==3)
			{
				Renderer_DrawTextSolid(&data->StoryText[1], 90, 400, Stroy_color);
			}
			if (data->Count == 4)
			{
				Renderer_DrawTextSolid(&data->StoryText[1], 90, 400, Stroy_color);
				Renderer_DrawTextSolid(&data->StoryText[2], 90, 450, Stroy_color);
			}
			if (data->Count == 5)
			{
				Renderer_DrawTextSolid(&data->StoryText[1], 90, 400, Stroy_color);
				Renderer_DrawTextSolid(&data->StoryText[2], 90, 450, Stroy_color);
				Renderer_DrawTextSolid(&data->StoryText[3], 90, 500, Stroy_color);
			}
		}
		if (data->Count == 6)
		{
			Renderer_DrawImage(&data->TestImage[2], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[1], 90, 400, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[2], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[3], 90, 500, Stroy_color);
			Renderer_DrawTextSolid(&data->ChoiceText[2], data->X, data->Y, choice_color);
		}
		if (data->Count == 7)
		{
			Renderer_DrawImage(&data->TestImage[2], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[1], 90, 400, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[2], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[3], 90, 500, Stroy_color);
			Renderer_DrawTextSolid(&data->ChoiceText[3], data->X, data->Y, choice_color);
		}
	}
	else if(data->Count <10)
	{
		Renderer_DrawImage(&data->TestImage[3], 0, 0);
		if (data->Count == 8)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[4], 90, 450, Stroy_color);
		}
		if (data->Count == 9)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[4], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[5], 90, 500, Stroy_color);
		}
	}
	else if (data->Count < 12)
	{
		Renderer_DrawImage(&data->TestImage[3], 0, 0);
		if (data->Count == 10)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[6], 90, 450, Stroy_color);
		}
		if (data->Count == 11)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[6], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[7], 90, 500, Stroy_color);
		}

	}
	else if (data->Count < 15)
	{
		Renderer_DrawImage(&data->TestImage[3], 0, 0);
		if (data->Count == 12)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[8], 90, 450, Stroy_color);
		}
		if (data->Count == 13)
		{
			Renderer_DrawImage(&data->TestImage[1], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[8], 90, 450, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[9], 90, 500, Stroy_color);
		}
		if (data->Count == 14)
		{
			Renderer_DrawImage(&data->TestImage[4], 0, 0);
			Renderer_DrawTextSolid(&data->StoryText[8], 90, 400, Stroy_color);
			Renderer_DrawTextSolid(&data->StoryText[9], 90, 450, Stroy_color);

			for (int i = 0; i < 2; i++)
			{
				if (i != count2)//���� �� �� �̿��� ������ ���
				{
					Renderer_DrawTextSolid(&data->ChoiceText[i + 4], data->X + i * teem, data->Y, color);
				}
				if (i == count2)
				{
					Renderer_DrawTextSolid(&data->ChoiceText[count2+4], data->X + count2 * teem, data->Y, choice_color);//������ ������ ���
				}
			}
		}
	}
#pragma endregion
}
void release_scene2(void)
{
	Senen2SceneData* data = (Senen2SceneData*)g_Scene.Data;

	for (int32 i = 0; i < STORY_TEXT_NUM_2; ++i)
	{
		Text_FreeText(&data->StoryText[i]);
	}
	for (int32 i = 0; i < CHOICE_TEXT_NUM_2; ++i)
	{
		Text_FreeText(&data->ChoiceText[i]);
	}
	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region Scene3
#define CHOICE_TEXT_NUM_3 6//������ ��
#define STORY_TEXT_NUM_3 10//���丮 ���ڿ� ��
#define IMG_NUM_3 5//�̹��� ��
#define FONT_SIZE_3 2//��Ʈ ������ ��

const wchar_t* Scene3_story[] = {
	L"���� �ƺ��� ������ ����شٰ� ����ؼ� ���ݾ�!",//���̼���
	L"�� ���� ����Ÿ�� ������ �Դϴ�.",
	L"����Ÿ���� �� 7������ �����Ǿ��ֽ��ϴ�.",
	L"1������ ���� ����Ʈ��, 2������ �׶�, 3�����¡�",//���� ����
	L"���� 31��� Ư���δ� �������̶�� ��ǰ� �����������̶��",
	L"��Ǹ� �Ӹ��ӿ� �ɵ��� �� ��Ȳ�� ���ص��� �ʴ´�.",
	L"�� �տ� �ִ� ���̴� �������� ���͵��� �� �� ���� �ǹ� �����̴�.",
	L"������ ������ ũ�� ������ �����ʾҴ�.",//����
	L"�������� ��������͸����δ� ������ �����ϴ�.",
	L"�ֺ��� �����Ͽ� �� �� ������ �����ؾ� �� �ʿ䰡 ������ ����."
};
const wchar_t* Scene3_choice[] = {
	L"���̿��� ����� �Ǽ��ΰŰ���.",
	L"�������� �����",
	L"(�ڽ��� �Ӹ��� �ο�������)",
	L"������ ����ϴ�.",
	L"���ź��� ������������, ȭ��ǿ� ���� ������ ����",
	L"���ڿ� ������ �ִ� �Ź��� Ȯ���Ѵ�."
};

typedef struct Senen3SceneData
{
	Text	ChoiceText[CHOICE_TEXT_NUM_3];
	Text	StoryText[STORY_TEXT_NUM_3];
	COORD	coord;
	int32	FontSize[FONT_SIZE_3];
	int32	RenderMode;
	Image	TestImage[IMG_NUM_3];
	int32	X;
	int32	Y;
	int32	Count;
} Senen3SceneData;

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


//�� �Լ�
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