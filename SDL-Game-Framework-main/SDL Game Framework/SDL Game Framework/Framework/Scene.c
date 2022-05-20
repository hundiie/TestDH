#include "stdafx.h"
#include "Scene.h"
#include "Csv.h"
#include "Framework.h"
#include "CSV_farser.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene_New

#define TEXT_NUM_0 3
#define IMG_NUM_0 6
const wchar_t* title_str[] = {
   L"���� ����",
   L"���� ����",
   L"����",
};

typedef struct TitleSceneNewData
{
	Text   Choice[TEXT_NUM_0];
	Text   TitleText;
	COORD   coord;
	int32   FontSize;
	int32   RenderMode;
	Image   TestImage[IMG_NUM_0];
	int32      X;
	int32      Y;
	int32   Alpha;
	int32   Alpha2;
	Music   BGM;
	float   Volume;
	float   ElapsedTime;
	float   Speed;
} TitleSceneNewData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneNewData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneNewData));

	TitleSceneNewData* data = (TitleSceneNewData*)g_Scene.Data;
	data->FontSize = 60;
	for (int32 i = 0; i < TEXT_NUM_0; ++i)
	{
		Text_CreateText(&data->Choice[i], "d2coding.ttf", data->FontSize, title_str[i], wcslen(title_str[i]));
	}
	Audio_LoadMusic(&data->BGM, "Jaesung.mp3");
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);
	Text_CreateText(&data->TitleText, "d2coding.ttf", 100, L"T I T L E", 9);
	Text_SetFontStyle(&data->TitleText, FS_BOLD);
	//data->RenderMode = BLENDED;
	Image_LoadImage(&data->TestImage[0], "NamSan.jpg");
	Image_LoadImage(&data->TestImage[1], "Choice_2_Script.png");
	Image_LoadImage(&data->TestImage[2], "WHITE.png");
	Image_LoadImage(&data->TestImage[3], "BLACK.png");
	Image_LoadImage(&data->TestImage[4], "EYEUP.png");
	Image_LoadImage(&data->TestImage[5], "EYEDOWN.png");

	data->Volume = 1.0f;
	data->Alpha = 0;
	data->Alpha2 = 255;
	data->Speed = 400.0f;
}
int count = 0;
void update_title(void)
{
	TitleSceneNewData* data = (TitleSceneNewData*)g_Scene.Data;

	if (count > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count--;
		}
	}
	if (count < TEXT_NUM_0 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count++;
		}
	}
	if (Input_GetKeyDown(VK_SPACE))
	{
		switch (count)
		{
		case 0:Scene_SetNextScene(SCENE_MAIN);
			break;
		case 1:exit(0);
			break;
			/*case 2:Scene_SetNextScene(SCENE_ENDING);
			   break;*/
		}
	}

	if (Input_GetKey(VK_CONTROL) & Input_GetKey(VK_F10))
	{
		Text_CreateText(&data->TitleText, "d2coding.ttf", 80, L"������ٺ�", 20);
	}

	if (Input_GetKey(VK_BACK))
	{
		Scene_SetNextScene(SCENE_TITLE);
	}



	/*if (count >= 0)
	{
	   data->Alpha = Clamp(0, data->Alpha - 1, 255);
	   Image_SetAlphaValue(&data->TestImage[0], data->Alpha);
	}*/


	if (count >= 0) //fade in, fade out
	{
		//data->Alpha = Clamp(0, data->Alpha + 1, 255); //�������¿��� ��ο����°� - ������� ���־ߴ�
		//Image_SetAlphaValue(&data->TestImage[0], data->Alpha);
		data->Alpha2 = Clamp(0, data->Alpha2 - 1, 255); //��ο��� ���¿��� ������� ��
		Image_SetAlphaValue(&data->TestImage[3], data->Alpha2);
	}
}

void render_title(void)
{
	TitleSceneNewData* data = (TitleSceneNewData*)g_Scene.Data;

	data->X = 900;//������ ���� X��ǥ
	data->Y = 400;//������ ���� Y��ǥ
	int teem = 100;//������ ������ �Ÿ�

	SDL_Color color = { .r = 255, .g = 255, .b = 255, };//�� ���� ����
	SDL_Color choice_color = { .g = 255 };//���� ����
	SDL_Color title_color = { .r = 100, .g = 100, .b = 100 };//���� ����

	Renderer_DrawImage(&data->TestImage[0], 0, 0);
	Renderer_DrawImage(&data->TestImage[3], 0, 0);
	//Renderer_DrawImage(&data->TestImage[4], 0, -200);


	for (int i = 0; i < TEXT_NUM_0; i++)
	{
		if (i != count)//���� �� �� �̿��� ������ ���
		{
			Renderer_DrawTextBlended(&data->Choice[i], data->X, data->Y + i * teem, color);
		}
		if (i == count)
		{
			Renderer_DrawTextBlended(&data->Choice[count], data->X, data->Y + count * teem + count, choice_color);//������ ������ ���
		}
	}
	Renderer_DrawTextBlended(&data->TitleText, 400, 80, title_color);//���� ������
}

void release_title(void)
{
	TitleSceneNewData* data = (TitleSceneNewData*)g_Scene.Data;

	for (int32 i = 0; i < TEXT_NUM_0; ++i)
	{
		Text_FreeText(&data->Choice[i]);
	}

	Audio_FreeMusic(&data->BGM);
	SafeFree(g_Scene.Data);
}

#pragma endregion 

#pragma region MainScene
#define Stringline 10


typedef struct MainData
{
	//csv
	int32	SCENE_NUMBER;		//1			��
	Text	STORY[Stringline];	//2			���
	Text	CHOICE[3];			//3 ,6 ,9	������
	int32	CHOICE_MOVE[3];		//4 ,7 ,10	������ �̵�
	SoundEffect	CHOICE_SOUND[3];//5 ,8 ,11	������ �Ҹ�
	Music	SOUND;				//12		�Ҹ�
	Text	IMAGE;				//13		�̹���
	int32	STORY_NUMBER;		//15		��� �� x
	int32	CHOICE_NUMBER;		//16		������ �� x
	
		//scene
	float	TIMER;				//Ÿ�̸�
	int32	FONT_SIZE;			//��Ʈ ������
	float	VOLUME;				//�Ҹ� ũ��
	Text	STORY_IMAGE;		//��� �̹���
	int32	CHOICE_COUNT[5];		//������ ī��Ʈ
} MainSceneData;

//ParseToUnicode(csvFile.Items[scene][2])//�����ڵ� (�ѱ�) ��������
//ParseToAscii(csvFile.Items[scene][2])//�ƽ�Ű �ڵ� (����) ��������
//ParseToInt (csvFile.Items[scene][1])//���� ��������

static int iscene = 1;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	char* fname = "GGAM.csv";//CSV���� �̸�
	CreateCsvFile(&csvFile, fname);
	
	data->SCENE_NUMBER = ParseToInt(csvFile.Items[iscene][1]);//�� �ѹ� ����
	data->STORY_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][15]);//��� �� ����
	data->CHOICE_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][16]);//������ �� ����
	data->FONT_SIZE = 30;// ��Ʈ ������ ����
	data->TIMER = 0.0f;//Ÿ�̸� �ʱ�ȭ
	data->VOLUME = 1.0f;//�Ҹ� ũ�� ����
	for (int i = 0; i < 5; i++)//ī���� �ʱ�ȭ
	{
		data->CHOICE_COUNT[i] = 0;
	}
	char* ttes2 = ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][2]);// ���丮 ����
	for (int i = 0; i < data->STORY_NUMBER; i++)// ���丮 ����
	{
		wchar_t* str2[100] = { L"" };
		ttes2 = StringLine(ttes2, str2);
		Text_CreateText(&data->STORY[i], "Chun_Bold.ttf", data->FONT_SIZE, str2, wcslen(str2));
	}
	if (data->CHOICE_NUMBER != 0)
	{
		for (int i = 0; i < data->CHOICE_NUMBER; i++)//������ ����ŭ ���� ���,�̵���,���� ����
		{
			Text_CreateText(&data->CHOICE[i], "Chun_Bold.ttf", data->FONT_SIZE, ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][3 + i * 3]), wcslen(ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][3 + i * 3])));
			data->CHOICE_MOVE[i] = ParseToInt(csvFile.Items[data->SCENE_NUMBER][4 + i * 3]);
			if (ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]) == NULL)
			{
				Audio_LoadSoundEffect(&data->CHOICE_SOUND[i], ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]));
			}
		}
	}

	Audio_LoadMusic(&data->SOUND, ParseToAscii(csvFile.Items[data->SCENE_NUMBER][12]));
	Audio_PlayFadeIn(&data->SOUND, INFINITY_LOOP, 3000);
	//Audio_HookMusicFinished(logOnFinished);
	//Audio_HookSoundEffectFinished(log2OnFinished);

	char* imageFile = ParseToAscii(csvFile.Items[data->SCENE_NUMBER][13]);
	Image_LoadImage(&data->IMAGE, imageFile);// �̹��� ���� 
	Image_LoadImage(&data->STORY_IMAGE, "7.png");// â ȭ�� �̹��� ����
	FreeCsvFile(&csvFile);//���� �ݱ�
	SafeFree(imageFile);
	Audio_Play(&data->SOUND, 1);
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	data->TIMER += Timer_GetDeltaTime();//�ð��� �ޱ�
	
	if (data->CHOICE_COUNT[1] < data->STORY_NUMBER)
	{
		if (Input_GetKeyDown(VK_SPACE))//���� ��ŵ ���
		{
			data->TIMER = 10;
		}
	}
	else if (data->CHOICE_NUMBER == 0)
	{
		if (Input_GetKeyDown(VK_SPACE))
		{
			iscene = data->SCENE_NUMBER + 1;
			Scene_SetNextScene(SCENE_MAIN);
			Audio_Stop();
		}
	}
	if (data->CHOICE_COUNT[2] == 1)
	{
		if (data->CHOICE_COUNT[0] < data->CHOICE_NUMBER - 1)
		{
			if (Input_GetKeyDown(VK_DOWN))
			{
				++data->CHOICE_COUNT[0];
			}
		}
		if (data->CHOICE_COUNT[0] > 0)
		{
			if (Input_GetKeyDown(VK_UP))
			{
				--data->CHOICE_COUNT[0];
			}
		}
		if (Input_GetKeyDown(VK_SPACE))//�������� ���� ���¿��� �����̽� �ٸ� ���� �� �̵�
		{
			switch (data->CHOICE_COUNT[0])
			{
			case 0:iscene = data->CHOICE_MOVE[0];
				Audio_Stop();
				Audio_PlaySoundEffect(&data->CHOICE_SOUND[0], 1);
				Scene_SetNextScene(SCENE_MAIN);
				break;
			case 1:iscene = data->CHOICE_MOVE[1];
				Audio_Stop();
				Audio_PlaySoundEffect(&data->CHOICE_SOUND[1], 1);
				Scene_SetNextScene(SCENE_MAIN);
				break;
			case 2:iscene = data->CHOICE_MOVE[2];
				Audio_Stop();
				Audio_PlaySoundEffect(&data->CHOICE_SOUND[2], 1);
				Scene_SetNextScene(SCENE_MAIN);
				break;
			}
		}
	}

	if (data->TIMER >= 1.0f && data->CHOICE_COUNT[1] <= data->STORY_NUMBER)//��ȭâ ī����
	{
		data->TIMER = 0.0f;
		data->CHOICE_COUNT[1]++;
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->IMAGE, 0, 0);
	Renderer_DrawImage(&data->STORY_IMAGE, 0, 0);
	
	SDL_Color color1 = {.r = 255, .g = 255, .b = 255, .a = 255};//�۾� ��
	SDL_Color color2 = {.r = 255, .g = 255, .b = 255, .a = 255};//������ �۾� ��(����)
	SDL_Color color3 = {.r = 255, .g = 255, .b = 0, .a = 255};//������ �۾� ��(�� ����)


	for (int i = 0; i < data->CHOICE_COUNT[1]; i++)//��� ���
	{
		Renderer_DrawTextBlended(&data->STORY[i], 50, 50 + i * (data->FONT_SIZE * 1.5), color1);
	}
	if (data->CHOICE_COUNT[1] > data->STORY_NUMBER && data->CHOICE_NUMBER != 0)
	{
		for (int i = 0; i < data->CHOICE_NUMBER; i++)//������ ���
		{
			if (data->CHOICE_COUNT[0] == i)
			{
				Renderer_DrawTextBlended(&data->CHOICE[i], 50, 450 + i * (data->FONT_SIZE * 2), color3);
			}
			else
			{
				Renderer_DrawTextBlended(&data->CHOICE[i], 50, 450 + i * (data->FONT_SIZE * 2), color2);
			}
			data->CHOICE_COUNT[2] = 1;//�������� ��µ��� ������ �Ѿ�� �ʰ� ī��Ʈ
		}
	}
	
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	for (int32 i = 0; i < data->STORY_NUMBER; ++i)
	{
		Text_FreeText(&data->STORY[i]);
	}
	for (int32 i = 0; i < data->CHOICE_NUMBER; ++i)
	{
		Text_FreeText(&data->CHOICE[i]);
		Audio_FreeSoundEffect(&data->CHOICE_SOUND[i]);
	}
	Audio_FreeMusic(&data->CHOICE_SOUND);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ENDING

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