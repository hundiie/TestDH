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
	Text_CreateText(&data->TitleText, "d2coding.ttf", 100, L" ", 9);
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
	
	Audio_StopSoundEffect();
	Audio_Stop();
	
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
		case 2:Scene_SetNextScene(SCENE_END);
			break;
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
	int32		SCENE_NUMBER;		//1			��
	Text		STORY[Stringline];	//2			���
	Text		CHOICE[3];			//3 ,6 ,9	������
	int32		CHOICE_MOVE[3];		//4 ,7 ,10	������ �̵�
	SoundEffect	CHOICE_SOUND[3];	//5 ,8 ,11	������ �Ҹ�
	Music		SOUND;				//12		�Ҹ�
	Image		IMAGE;				//13		�̹���
	int32		MOTION;				//14		ȿ��
	int32		STORY_NUMBER;		//15		��� �� x
	int32		CHOICE_NUMBER;		//16		������ �� x
		//scene
	float		TIMER;				//Ÿ�̸�
	int32		FONT_SIZE;			//��Ʈ ������
	float		VOLUME;				//�Ҹ� ũ��
	int32		CHOICE_COUNT[5];	//������ ī��Ʈ 0: ������ ���� 1: ���� �� ��ŭ ��ŵ ī��Ʈ 2: ������ ��� �� ��ŵ ���� �� 3�ѱ�� ī��Ʈ
	float		EARTH;				//���� Ÿ�̸�
	float		NEXT;
	int32		X;
	int32		Y;
	Image		STORY_IMAGE;		//��� �̹���
	Image		BLACK_IMAGE;		//��� �̹���
	int32		Alpha;
} MainSceneData;

char* EFFECT[3];//���� ����
int effect_count = 0;//��� ���� ������� üũ
int effect_off[3] = { 0, 0, 0 } ;//���尡 �ִ��� ������ üũ
bool effect_switch = FALSE;

//ParseToUnicode(csvFile.Items[scene][2])//�����ڵ� (�ѱ�) ��������
//ParseToAscii(csvFile.Items[scene][2])//�ƽ�Ű �ڵ� (����) ��������
//ParseToInt (csvFile.Items[scene][1])//���� ��������
void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

static int iscene = 1;

SoundEffect	C_SOUND[3];
char* wav[3];
int wav_t = 0;
int wav_s = 0;

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	CsvFile csvFile;
	memset(&csvFile, 0, sizeof(CsvFile));
	char* fname = "GGAM.csv";//CSV���� �̸�
	CreateCsvFile(&csvFile, fname);
	
	int32 scene_number = ParseToInt(csvFile.Items[iscene][1]);//�� �ѹ� ����
	int16 motion = ParseToInt(csvFile.Items[data->SCENE_NUMBER][14]);//ȿ�� �ѹ� ����
	data->SCENE_NUMBER = scene_number;
	data->MOTION = motion;
	data->STORY_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][15]);//��� �� ����
	data->CHOICE_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][16]);//������ �� ����
	data->FONT_SIZE = 30;// ��Ʈ ������ ����
	data->TIMER = 0.0f;//Ÿ�̸� �ʱ�ȭ
	data->VOLUME = 1.0f;//�Ҹ� ũ�� ����
	data->EARTH = 0.0f;//���� Ÿ�̸�
	data->X = 0;
	data->Y = 0;

	switch (data->MOTION)
	{
	case 1:data->Alpha = 255;
		break;
	case 2:data->Alpha = 0;
		break;
	default:
		break;
	}
	
	for (int i = 0; i < 5; i++)//ī���� �ʱ�ȭ
	{
		data->CHOICE_COUNT[i] = 0;
	}
	char* ttes1 = ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][2]);// ���丮 ����
	char* ttes2 = ttes1;
	SafeFree(ttes1);
	for (int i = 0; i < data->STORY_NUMBER; i++)// ���丮 ����
	{
		wchar_t* str2[100] = { L"" };
		ttes2 = StringLine(ttes2, str2);
		Text_CreateText(&data->STORY[i], "Chun_Bold.ttf", data->FONT_SIZE, str2, wcslen(str2));
	}
	
	if (iscene != 0)
	{
		for (int i = 0; i < wav_s; i++)// ���� �����Ϳ� �߰�
		{
			if (*wav[i] != '\0')
			{
				//Audio_LoadSoundEffect(&data->CHOICE_SOUND[i], wav[i]);
				Audio_LoadSoundEffect(&C_SOUND[i], wav[i]);
			}
		}
	}

	if (data->CHOICE_NUMBER != 0)
	{
		for (int i = 0; i < data->CHOICE_NUMBER; i++)//������ ����ŭ ���� ���,�̵���,���� ����
		{
			Text_CreateText(&data->CHOICE[i], "Chun_Bold.ttf", data->FONT_SIZE, ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][3 + i * 3]), wcslen(ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][3 + i * 3])));
			data->CHOICE_MOVE[i] = ParseToInt(csvFile.Items[data->SCENE_NUMBER][4 + i * 3]);
			wav[i] = ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]);
		}
	}
	wav_s = data->CHOICE_NUMBER;
	//Audio_LoadSoundEffect(&data->CHOICE_SOUND[i], ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]));
	/*if (ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]) == NULL)
	{
		Audio_LoadSoundEffect(&data->CHOICE_SOUND[i], ParseToAscii(csvFile.Items[data->SCENE_NUMBER][5 + i * 3]));
	}*/
	Audio_LoadMusic(&data->SOUND, ParseToAscii(csvFile.Items[data->SCENE_NUMBER][12]));
	Audio_PlayFadeIn(&data->SOUND, INFINITY_LOOP, 3000);
	Audio_SetVolume(data->VOLUME);

	Audio_HookSoundEffectFinished(log2OnFinished);

	char* imageFile = ParseToAscii(csvFile.Items[data->SCENE_NUMBER][13]);
	Image_LoadImage(&data->IMAGE, imageFile);// �̹��� ���� 
	char imageFile1[128] = "7.png";
	Image_LoadImage(&data->STORY_IMAGE, imageFile1);// â ȭ�� �̹��� ����
	//SafeFree(imageFile2);
	if (data->MOTION == 1 || data->MOTION == 2)
	{
		char imageFile2[128] = "BLACK.png";
		Image_LoadImage(&data->BLACK_IMAGE, imageFile2);// ���� ȭ�� �̹��� ����
	}
	SafeFree(imageFile);
	Audio_Play(&data->SOUND, 1);
	FreeCsvFile(&csvFile);//���� �ݱ�
}

void update_main(void)
{
	if (iscene == 0)//0���� Ÿ��Ʋ�� �̵�
	{
		Scene_SetNextScene(SCENE_TITLE);
		iscene = 1;
	}

	if (iscene == 118)//118���� �������� �̵�
	{
		Scene_SetNextScene(SCENE_END);
		iscene = 1;
	}
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	if (iscene ==4)
	{
		Audio_StopSoundEffect();
	}
	data->TIMER += Timer_GetDeltaTime();//�ð��� �ޱ�
	data->EARTH += Timer_GetDeltaTime();//�ð��� �ޱ�
	data->NEXT += Timer_GetDeltaTime();//�ð��� �ޱ�

	if (data->MOTION > 0)
	{
		switch (data->MOTION)
		{
		case 1://����
			data->Alpha = Clamp(0, data->Alpha - 1, 255);
			break;
		case 3://���� ȿ��

			data->X = Random_GetNumberFromRange(-20, 20);
			data->Y = Random_GetNumberFromRange(-20, 20);
			
			if (data->EARTH > 2.0f)
			{
				data->X = 0;
				data->Y = 0;
				data->MOTION = 0;
			}
			break;
		default:
			break;
		}
	}
	if (wav_t != 0)//�Ҹ� ���
	{
		
		if (iscene < 80)
		{
			Audio_StopSoundEffect();
		}

		switch (wav_t)
		{
		case 1:
			Audio_PlaySoundEffect(&C_SOUND[0], 1);//������ 1
			wav_t = 0;
			break;
		case 2:Audio_PlaySoundEffect(&C_SOUND[1], 1);//������ 2
			wav_t = 0;
			break;
		case 3:Audio_PlaySoundEffect(&C_SOUND[2], 1);//������ 3
			wav_t = 0;
			break;
		default:
			break;
		}
	}

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
				wav_t = 1;
				if (data->MOTION == 2)//���� �����
				{
					data->CHOICE_COUNT[3] = 1;
				}

				if (data->MOTION !=2)
				{
					Scene_SetNextScene(SCENE_MAIN);
				}
				break;
			case 1:iscene = data->CHOICE_MOVE[1];
				Audio_Stop();
				wav_t = 2;
				if (data->MOTION == 2)//���� �����
				{
					data->CHOICE_COUNT[3] = 1;
				}
				if (data->MOTION != 2)
				{
					Scene_SetNextScene(SCENE_MAIN);
				}
				break;
			case 2:iscene = data->CHOICE_MOVE[2];
				Audio_Stop();
				wav_t = 3;
				if (data->MOTION == 2)//���� �����
				{
					data->CHOICE_COUNT[3] = 1;
				}
				if (data->MOTION != 2)
				{
					Scene_SetNextScene(SCENE_MAIN);
				}
				break;
			}
		}
	}

	if (data->CHOICE_COUNT[3] == 1 && data->MOTION == 2)
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		
		if (data->Alpha >= 255)
		{
			Scene_SetNextScene(SCENE_MAIN);
		}
	}

	if (data->TIMER >= 1.0f && data->CHOICE_COUNT[1] <= data->STORY_NUMBER)//��ȭâ ī����
	{
		data->TIMER = 0.0f;
		data->CHOICE_COUNT[1]++;
	}
	Image_SetAlphaValue(&data->BLACK_IMAGE, data->Alpha);
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	Renderer_DrawImage(&data->IMAGE, data->X, data->Y);
	Renderer_DrawImage(&data->STORY_IMAGE, 0, 0);
	if (data->MOTION == 1)
	{
		Renderer_DrawImage(&data->BLACK_IMAGE, 0, 0);
	}
	
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
	if (data->MOTION == 2)
	{
		Renderer_DrawImage(&data->BLACK_IMAGE, 0, 0);
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
	Audio_FreeMusic(&data->SOUND);
	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region ENDING
typedef struct EndingSceneNewData
{
	Text   EndingText;
	Text   EndingText2;
	Text   EndingText3;
	Text   EndingText4;
	Text   EndingText5;
	COORD   coord;
	int32   FontSize;
	Image   TestImage[IMG_NUM_0];
	int32      X;
	int32      Y;
	int32      X2;
	int32      Y2;
	int32   Alpha;
	int32   Alpha2;
	Music   BGM;
	float   Volume;
	float   ElapsedTime;
	int   Speed;
	int32   R;
	int32   G;
	int32   B;
	int32   Count;
} EndingSceneNewData;

void init_end(void)
{
	g_Scene.Data = malloc(sizeof(EndingSceneNewData));
	memset(g_Scene.Data, 0, sizeof(EndingSceneNewData));
	EndingSceneNewData* data = (EndingSceneNewData*)g_Scene.Data;
	Audio_LoadMusic(&data->BGM, "Brother_Jaesung.mp3");
	Image_LoadImage(&data->TestImage, "Black.png");
	Text_CreateText(&data->EndingText, "d2coding.ttf", 80, L"Thank you for playing", 21);
	Text_CreateText(&data->EndingText2, "d2coding.ttf", 40, L"�׽����ư� �Բ�", 8);

	Audio_Play(&data->BGM, INFINITY_LOOP);
	data->R = 255;
	data->G = 255;
	data->B = 255;
	data->Volume = 1.0f;
	data->Alpha = 0;
	data->Alpha2 = 0;
	data->Speed = 1;
	data->X = 300;
	data->Y = 400;
	data->X2 = 500;
	data->Y2 = 750;
	data->Count = 0;
}
void update_end(void)
{
	EndingSceneNewData* data = (EndingSceneNewData*)g_Scene.Data;
	if (data->Y < -100)
	{
		data->X = 500;
		data->Y = 750;
		data->Count++;

		switch (data->Count) // Ư�� ��ġ���� �ʱ�ȭ �� �ؽ�Ʈ �ٲ�
		{
		case 1:
			Text_CreateText(&data->EndingText, "d2coding.ttf", 40, L"����: ������, �̴���", 12);
			break;
		case 3:
			Text_CreateText(&data->EndingText, "d2coding.ttf", 40, L"����: ȫ����, ���翬", 12);
			break;
		case 5:
			Scene_SetNextScene(SCENE_TITLE);
			Audio_Stop();
			break;
		}
	}

	if (data->Y2 < -100)
	{
		data->X2 = 500;
		data->Y2 = 750;
		data->Count++;

		switch (data->Count)// Ư�� ��ġ���� �ʱ�ȭ �� �ؽ�Ʈ �ٲ� �ι�°,
		{
		case 2:
			Text_CreateText(&data->EndingText2, "d2coding.ttf", 40, L"����: �Ǽ���, ������", 12);
			break;
		case 4:
			Text_CreateText(&data->EndingText2, "d2coding.ttf", 40, L"", 12);
			break;
		}

	}

	data->Alpha = data->Alpha + 1;
	if (data->Alpha > 255)
	{
		data->Alpha = 255;
	}

	if (data->Alpha >= 200) // ���İ��� 200�Ǹ� ������
	{
		data->Y = data->Y - data->Speed;

		data->Alpha2 = data->Alpha2 + 1;
		data->Y2 = data->Y2 - data->Speed;
	}

	if (data->Alpha2 > 255)
	{
		data->Alpha2 = 255;
	}

	if (Input_GetKeyDown(VK_SPACE)) // �ӵ�����
	{
		data->Speed = 3;
	}

	if (Input_GetKeyUp(VK_SPACE))
	{
		data->Speed = 1;
	}

	if (Input_GetKeyUp(VK_ESCAPE))// �ڷΰ���
	{
		Scene_SetNextScene(SCENE_TITLE);
		Audio_Stop();
	}

}
void render_end(void)
{

	EndingSceneNewData* data = (EndingSceneNewData*)g_Scene.Data;
	SDL_Color TextColor = { .r = 255, .g = 255, .b = 255, .a = data->Alpha };//�۾� ��
	SDL_Color TextColor2 = { .r = data->R - (rand() * 2), .g = data->G - (rand() * 2), .b = data->B - (rand() * 2), .a = data->Alpha2 };//�۾� ��
	Renderer_DrawImage(&data->TestImage, 0, 0);
	Renderer_DrawTextBlended(&data->EndingText, data->X, data->Y, TextColor);
	Renderer_DrawTextBlended(&data->EndingText2, data->X2, data->Y2, TextColor2);
	if (data->Y < -80)
	{
		TextColor = TextColor2;
	}
}
void release_end(void)
{
	EndingSceneNewData* data = (EndingSceneNewData*)g_Scene.Data;
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