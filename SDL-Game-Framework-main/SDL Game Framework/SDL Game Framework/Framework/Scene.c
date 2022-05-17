#include "stdafx.h"
#include "Scene.h"
#include "Timer.h"

#include "Framework.h"


#define SOLID 0
#define SHADED 1
#define BLENDED 2
Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;


#pragma region TitleScene


#define SOLID 0
#define SHADED 1
#define BLENDED 2

//���� ��
const wchar_t* str[] = {
   L"���� ����",
   L"���� ����",
};
#define FONT_SIZE1 20//��Ʈ ũ��
#define TEXT_NUM1 2//���� ����

typedef struct TitleSceneData
{
	Text   GuideLine[TEXT_NUM1];
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage;
	int32      X;
	int32      Y;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;


	data->FontSize = FONT_SIZE1;//��Ʈ ũ�� ����

	

	for (int32 i = 0; i < TEXT_NUM1; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", data->FontSize, str[i], wcslen(str[i]));

	}

	Image_LoadImage(&data->TestImage, "Background.jfif");// �̹��� �ε�
}

int count = 0;//������ �ѹ�

void update_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	if (count > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count--;//������ �ø���
		}
	}
	if (count < TEXT_NUM1 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count++;//������ ������
		}
	}
	if (Input_GetKeyDown('R'))//������ ���ϴ� ���
	{
		switch (count)
		{
		case 0:Scene_SetNextScene(SCENE_SCENE2);
			break;
		case 1:Scene_SetNextScene(SCENE_SCENE3);
			break;
		default:
			break;
		}
		
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	//data->X = rand() % 1020;
	//data->Y = rand() % 200;

	data->X = 510;//�׸� ��ġ ����
	data->Y = 100;

	SDL_Color color = { .a = 255 };//���� 
	SDL_Color choice_color = { .g = 255 };

	Renderer_DrawImage(&data->TestImage, data->X, data->Y);// �̹��� ����

	for (int32 i = 0; i < TEXT_NUM1; ++i)
	{
		Renderer_DrawTextSolid(&data->GuideLine[i], 800, 300 + i * data->FontSize, color);
		
	}
	Renderer_DrawTextSolid(&data->GuideLine[count], 800, 300 + count * data->FontSize, choice_color);
}

void release_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM1; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region Scene2

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//���� ��
const wchar_t* str_story2[] = {
   L"������ �ҽ���ġ�� ���� ���� �߰� �Ǿ���.",
   L"���� �߰� ���� �տ��� ���� ���̰� �־��� ���� ���� �ƺ��� �ҷ���.",
   L"�� ��� ��Ȳ�� ������Ͽ� �ֺ��� �ѷ�����.",
};

const wchar_t* str_choice2[] = {
   L"1. �������� ������ ����� �����.",
   L"2. �տ� �ִ� ���̿��� �����. ",
};

#define FONT_SIZE_ST2 30//��Ʈ ũ��
#define FONT_SIZE_CO2 20//��Ʈ ũ��
#define TEXT_NUM_ST2 3//���� ����
#define TEXT_NUM_CO2 2//���� ����

typedef struct Scene2Data
{
	Text    story[TEXT_NUM_ST2];
	Text    choice[TEXT_NUM_CO2];
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage;
	int32      X;
	int32      Y;
} Scene2Data;

void init_scene2(void)
{
	g_Scene.Data = malloc(sizeof(Scene2Data));
	memset(g_Scene.Data, 0, sizeof(Scene2Data));

	Scene2Data* data = (Scene2Data*)g_Scene.Data;


	data->FontSize = FONT_SIZE_ST2;//��Ʈ ũ�� ����
	data->FontSize = FONT_SIZE_CO2;//��Ʈ ũ�� ����



	for (int32 i = 0; i < TEXT_NUM_ST2; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->story[i], "d2coding.ttf", data->FontSize, str_story2[i], wcslen(str_story2[i]));
	}
	for (int32 i = 0; i < TEXT_NUM_CO2; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->choice[i], "d2coding.ttf", data->FontSize, str_choice2[i], wcslen(str_choice2[i]));
	}

	Image_LoadImage(&data->TestImage, "Background.jfif");// �̹��� �ε�
}

int count_ch2 = 0;//������ �ѹ�

void update_scene2(void)
{
	Scene2Data* data = (Scene2Data*)g_Scene.Data;

	if (count_ch2 > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count_ch2--;//������ �ø���
		}
	}

	if (count_ch2< TEXT_NUM_CO2 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count_ch2++;//������ ������
		}
	}

	if (Input_GetKeyDown('R'))
	{
		Scene_SetNextScene(SCENE_SCENE3);
	}
}

void render_scene2(void)
{
	
	Scene2Data* data = (Scene2Data*)g_Scene.Data;
	//data->X = rand() % 1020;
	//data->Y = rand() % 200;

	data->X = 510;//�׸� ��ġ ����
	data->Y = 100;

	SDL_Color color = { .a = 255 };//���� 
	SDL_Color choice_color = { .g = 255 };

	Renderer_DrawImage(&data->TestImage, data->X, data->Y);// �̹��� ����

	for (int32 i = 0; i < TEXT_NUM_ST2; ++i)//���丮
	{
		Renderer_DrawTextSolid(&data->story[i], 150, 450 + i * data->FontSize, color);
	}

	for (int32 i = 0; i < TEXT_NUM_CO2; ++i)//������
	{
		Renderer_DrawTextSolid(&data->choice[i], 150, 620 + i * data->FontSize, color);
	}

	Renderer_DrawTextSolid(&data->choice[count_ch2], 150, 620 + count_ch2 * data->FontSize, choice_color);
}

void release_scene2(void)
{
	Scene2Data* data = (Scene2Data*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_ST2; ++i)
	{
		Text_FreeText(&data->story[i]);
	}

	for (int32 i = 0; i < TEXT_NUM_CO2; ++i)
	{
		Text_FreeText(&data->choice[i]);
	}

	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region Scene3

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//���� ��
const wchar_t* str_story3[] = {
   L"����� ����Ÿ�� ������ �Դϴ�.",
   L"����Ÿ�� �����뿡 ���� ������ ������ �Ѵ�.",
   L"\"����Ÿ���� �� 7������ �����Ǿ������� 1������ ���� ����Ʈ��,",
   L"2������ �׶�, 3������ ��..\"",
   L"������ �Ӹ��� �ο���Ҵ�.",
};

const wchar_t* str_choice3[] = {
   L"1. ������ �ƽ��ϴ�...",
   L" ",
};

#define FONT_SIZE_ST3 30//��Ʈ ũ��
#define FONT_SIZE_CO3 20//��Ʈ ũ��
#define TEXT_NUM_ST3 5//���� ����
#define TEXT_NUM_CO3 2//���� ����

typedef struct Scene3Data
{
	Text    story[TEXT_NUM_ST3];
	Text    choice[TEXT_NUM_CO3];
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage;
	int32      X;
	int32      Y;
} Scene3Data;

void init_scene3(void)
{
	g_Scene.Data = malloc(sizeof(Scene3Data));
	memset(g_Scene.Data, 0, sizeof(Scene3Data));

	Scene3Data* data = (Scene3Data*)g_Scene.Data;


	data->FontSize = FONT_SIZE_ST3;//��Ʈ ũ�� ����
	data->FontSize = FONT_SIZE_CO3;//��Ʈ ũ�� ����

	

	for (int32 i = 0; i < TEXT_NUM_ST3; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->story[i], "d2coding.ttf", data->FontSize, str_story3[i], wcslen(str_story3[i]));
	}
	for (int32 i = 0; i < TEXT_NUM_CO3; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->choice[i], "d2coding.ttf", data->FontSize, str_choice3[i], wcslen(str_choice3[i]));
	}

	Image_LoadImage(&data->TestImage, "Background.jfif");// �̹��� �ε�
}

int count_ch3 = 0;//������ �ѹ�

void update_scene3(void)
{
	Scene3Data* data = (Scene3Data*)g_Scene.Data;

	if (count_ch3 > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count_ch3--;//������ �ø���
		}
	}

	if (count_ch3 < TEXT_NUM_CO3 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count_ch3++;//������ ������
		}
	}

	if (Input_GetKeyDown('R'))
	{
		Scene_SetNextScene(SCENE_SCENE4);
	}
}

void render_scene3(void)
{
	Scene3Data* data = (Scene3Data*)g_Scene.Data;
	//data->X = rand() % 1020;
	//data->Y = rand() % 200;

	data->X = 510;//�׸� ��ġ ����
	data->Y = 100;

	SDL_Color color = { .a = 255 };//���� 
	SDL_Color choice_color = { .g = 255 };

	Renderer_DrawImage(&data->TestImage, data->X, data->Y);// �̹��� ����

	for (int32 i = 0; i < TEXT_NUM_ST3; ++i)//���丮
	{
		Renderer_DrawTextSolid(&data->story[i], 150, 450 + i * data->FontSize, color);
	}

	for (int32 i = 0; i < TEXT_NUM_CO3; ++i)//������
	{
		Renderer_DrawTextSolid(&data->choice[i], 150, 620 + i * data->FontSize, color);
	}

	Renderer_DrawTextSolid(&data->choice[count_ch3], 150, 620 + count_ch3 * data->FontSize, choice_color);
}

void release_scene3(void)
{
	Scene3Data* data = (Scene3Data*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_ST3; ++i)
	{
		Text_FreeText(&data->story[i]);
	}
	
	for (int32 i = 0; i < TEXT_NUM_CO3; ++i)
	{
		Text_FreeText(&data->choice[i]);
	}

	SafeFree(g_Scene.Data);
}

#pragma endregion

#pragma region Scene4

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//���� ��
const wchar_t* str_story4[] = {
   L"�ƺ��� ����ڰ� �ؼ� �°��ݾ�!",
   L" ",
};

const wchar_t* str_choice4[] = {
   L"1. ���̿��� ������� �߸��ΰ� ����. �������� �����",
   L" ",
};

#define FONT_SIZE_ST4 30//��Ʈ ũ��
#define FONT_SIZE_CO4 20//��Ʈ ũ��
#define TEXT_NUM_ST4 2//���� ����
#define TEXT_NUM_CO4 2//���� ����

typedef struct Scene4Data
{
	Text    story[TEXT_NUM_ST4];
	Text    choice[TEXT_NUM_CO4];
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage;
	int32      X;
	int32      Y;
} Scene4Data;

void init_scene4(void)
{
	g_Scene.Data = malloc(sizeof(Scene4Data));
	memset(g_Scene.Data, 0, sizeof(Scene4Data));

	Scene4Data* data = (Scene4Data*)g_Scene.Data;

	data->FontSize = FONT_SIZE_ST4;//��Ʈ ũ�� ����
	data->FontSize = FONT_SIZE_CO4;//��Ʈ ũ�� ����


	for (int32 i = 0; i < TEXT_NUM_ST4; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->story[i], "d2coding.ttf", data->FontSize, str_story4[i], wcslen(str_story4[i]));
	}
	for (int32 i = 0; i < TEXT_NUM_CO3; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->choice[i], "d2coding.ttf", data->FontSize, str_choice4[i], wcslen(str_choice4[i]));
	}

	Image_LoadImage(&data->TestImage, "Background.jfif");// �̹��� �ε�
}

int count_ch4 = 0;//������ �ѹ�

void update_scene4(void)
{
	Scene4Data* data = (Scene4Data*)g_Scene.Data;

	if (count_ch4 > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count_ch4--;//������ �ø���
		}
	}

	if (count_ch4 < TEXT_NUM_CO4 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count_ch4++;//������ ������
		}
	}

	if (Input_GetKeyDown('R'))
	{
		Scene_SetNextScene(SCENE_SCENE5);
	}
}

void render_scene4(void)
{
	Scene4Data* data = (Scene4Data*)g_Scene.Data;
	//data->X = rand() % 1020;
	//data->Y = rand() % 200;

	data->X = 510;//�׸� ��ġ ����
	data->Y = 100;

	SDL_Color color = { .a = 255 };//���� 
	SDL_Color choice_color = { .g = 255 };

	Renderer_DrawImage(&data->TestImage, data->X, data->Y);// �̹��� ����

	for (int32 i = 0; i < TEXT_NUM_ST4; ++i)//���丮
	{
		Renderer_DrawTextSolid(&data->story[i], 150, 450 + i * data->FontSize, color);
	}

	for (int32 i = 0; i < TEXT_NUM_CO4; ++i)//������
	{
		Renderer_DrawTextSolid(&data->choice[i], 150, 620 + i * data->FontSize, color);
	}

	Renderer_DrawTextSolid(&data->choice[count_ch4], 150, 620 + count_ch4 * data->FontSize, choice_color);
}

void release_scene4(void)
{
	Scene4Data* data = (Scene4Data*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_ST4; ++i)
	{
		Text_FreeText(&data->story[i]);
	}

	for (int32 i = 0; i < TEXT_NUM_CO4; ++i)
	{
		Text_FreeText(&data->choice[i]);
	}

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region Scene5

#define SOLID 0
#define SHADED 1
#define BLENDED 2

//���� ��
const wchar_t* str_story5[] = {
   L"���� OO��� Ư���δ� ���� �������̶�� ��Ǹ� �Ӹ��ӿ��� �ɵ��� �� ��Ȳ�� ���ذ� ���� �ʴ´�.",
   L"�� �տ� �ִ� ���̴� �������� ���� �� ���ڱ� ����Ÿ���� �ִ� ������",
   L"�� �տ� �ִ� ���̴� �������� ���� �� ���ڱ� ����Ÿ���� �ִ� ������",
   L"���͵��� �� �� ���� �ǹ� �����̿���.",
   L"�������� ���� �͸����δ� ������ �����ϴ� �ֺ��� �����Ͽ� �� �� ������ ��ƺ���.",
   L"",
};

const wchar_t* str_choice5[] = {
   L"1. ���ź��� ������������ ȭ��ǿ� ���� ������ ����",
   L"2. ���ڿ� ���� �Ź��� Ȯ���Ѵ�.",
};

#define FONT_SIZE_ST5 30//��Ʈ ũ��
#define FONT_SIZE_CO5 20//��Ʈ ũ��
#define TEXT_NUM_ST5 6//���� ����
#define TEXT_NUM_CO5 2//���� ����

typedef struct Scene5Data
{
	Text    story[TEXT_NUM_ST5];
	Text    choice[TEXT_NUM_CO5];
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage;
	int32      X;
	int32      Y;
} Scene5Data;

void init_scene5(void)
{
	g_Scene.Data = malloc(sizeof(Scene5Data));
	memset(g_Scene.Data, 0, sizeof(Scene5Data));

	Scene5Data* data = (Scene5Data*)g_Scene.Data;

	data->FontSize = FONT_SIZE_ST5;//��Ʈ ũ�� ����
	data->FontSize = FONT_SIZE_CO5;//��Ʈ ũ�� ����


	for (int32 i = 0; i < TEXT_NUM_ST5; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->story[i], "d2coding.ttf", data->FontSize, str_story5[i], wcslen(str_story5[i]));
	}
	for (int32 i = 0; i < TEXT_NUM_CO3; ++i)
	{
		data->RenderMode = SHADED;
		Text_CreateText(&data->choice[i], "d2coding.ttf", data->FontSize, str_choice5[i], wcslen(str_choice5[i]));
	}

	Image_LoadImage(&data->TestImage, "Background.jfif");// �̹��� �ε�
}

int count_ch5 = 0;//������ �ѹ�

void update_scene5(void)
{
	Scene5Data* data = (Scene5Data*)g_Scene.Data;

	if (count_ch5 > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count_ch5--;//������ �ø���
		}
	}

	if (count_ch5 < TEXT_NUM_CO5 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count_ch5++;//������ ������
		}
	}
	//if (Input_GetKeyDown('R'))//������ ���ϴ� ���
	//{
	//	switch (count_s2)
	//	{
	//	case 0:Scene_SetNextScene(SCENE_MAIN);
	//		break;
	//	case 1:Scene_SetNextScene(SCENE_MAIN);
	//		break;
	//	default:
	//		break;
	//	}
	//	
	//}
}

void render_scene5(void)
{
	Scene5Data* data = (Scene5Data*)g_Scene.Data;
	//data->X = rand() % 1020;
	//data->Y = rand() % 200;

	data->X = 510;//�׸� ��ġ ����
	data->Y = 100;

	SDL_Color color = { .a = 255 };//���� 
	SDL_Color choice_color = { .g = 255 };

	Renderer_DrawImage(&data->TestImage, data->X, data->Y);// �̹��� ����

	for (int32 i = 0; i < TEXT_NUM_ST5; ++i)//���丮
	{
		Renderer_DrawTextSolid(&data->story[i], 150, 450 + i * data->FontSize, color);
	}

	for (int32 i = 0; i < TEXT_NUM_CO5; ++i)//������
	{
		Renderer_DrawTextSolid(&data->choice[i], 150, 620 + i * data->FontSize, color);
	}

	Renderer_DrawTextSolid(&data->choice[count_ch5], 150, 620 + count_ch5 * data->FontSize, choice_color);
}

void release_scene5(void)
{
	Scene5Data* data = (Scene5Data*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_ST5; ++i)
	{
		Text_FreeText(&data->story[i]);
	}

	for (int32 i = 0; i < TEXT_NUM_CO5; ++i)
	{
		Text_FreeText(&data->choice[i]);
	}

	SafeFree(g_Scene.Data);
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