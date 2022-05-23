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
   L"게임 시작",
   L"게임 종료",
   L"제작",
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
		Text_CreateText(&data->TitleText, "d2coding.ttf", 80, L"노우진바보", 20);
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
		//data->Alpha = Clamp(0, data->Alpha + 1, 255); //밝은상태에서 어두워지는것 - 검정배경 없애야댐
		//Image_SetAlphaValue(&data->TestImage[0], data->Alpha);
		data->Alpha2 = Clamp(0, data->Alpha2 - 1, 255); //어두워진 상태에서 밝아지는 것
		Image_SetAlphaValue(&data->TestImage[3], data->Alpha2);
	}
}

void render_title(void)
{
	TitleSceneNewData* data = (TitleSceneNewData*)g_Scene.Data;

	data->X = 900;//선택지 시작 X좌표
	data->Y = 400;//선택지 시작 Y좌표
	int teem = 100;//석택지 사이의 거리

	SDL_Color color = { .r = 255, .g = 255, .b = 255, };//비 선택 색깔
	SDL_Color choice_color = { .g = 255 };//선택 색깔
	SDL_Color title_color = { .r = 100, .g = 100, .b = 100 };//제목 색깔

	Renderer_DrawImage(&data->TestImage[0], 0, 0);
	Renderer_DrawImage(&data->TestImage[3], 0, 0);
	//Renderer_DrawImage(&data->TestImage[4], 0, -200);


	for (int i = 0; i < TEXT_NUM_0; i++)
	{
		if (i != count)//선택 한 것 이외의 선택지 출력
		{
			Renderer_DrawTextBlended(&data->Choice[i], data->X, data->Y + i * teem, color);
		}
		if (i == count)
		{
			Renderer_DrawTextBlended(&data->Choice[count], data->X, data->Y + count * teem + count, choice_color);//선택한 선택지 출력
		}
	}
	Renderer_DrawTextBlended(&data->TitleText, 400, 80, title_color);//제목 랜더링
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
	int32		SCENE_NUMBER;		//1			씬
	Text		STORY[Stringline];	//2			대사
	Text		CHOICE[3];			//3 ,6 ,9	선택지
	int32		CHOICE_MOVE[3];		//4 ,7 ,10	선택지 이동
	SoundEffect	CHOICE_SOUND[3];	//5 ,8 ,11	선택지 소리
	Music		SOUND;				//12		소리
	Image		IMAGE;				//13		이미지
	int32		MOTION;				//14		효과
	int32		STORY_NUMBER;		//15		대사 수 x
	int32		CHOICE_NUMBER;		//16		선택지 수 x
		//scene
	float		TIMER;				//타이머
	int32		FONT_SIZE;			//폰트 사이즈
	float		VOLUME;				//소리 크기
	int32		CHOICE_COUNT[5];	//선택지 카운트 0: 선택지 조절 1: 글자 수 만큼 스킵 카운트 2: 선택지 출력 전 스킵 제한 용 3넘기기 카운트
	float		EARTH;				//지진 타이머
	float		NEXT;
	int32		X;
	int32		Y;
	Image		STORY_IMAGE;		//대사 이미지
	Image		BLACK_IMAGE;		//대사 이미지
	int32		Alpha;
} MainSceneData;

char* EFFECT[3];//음악 저장
int effect_count = 0;//몇번 사운드 재생할지 체크
int effect_off[3] = { 0, 0, 0 } ;//사운드가 있는지 없는지 체크
bool effect_switch = FALSE;

//ParseToUnicode(csvFile.Items[scene][2])//유니코드 (한글) 가져오기
//ParseToAscii(csvFile.Items[scene][2])//아스키 코드 (영어) 가져오기
//ParseToInt (csvFile.Items[scene][1])//정수 가져오기
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
	char* fname = "GGAM.csv";//CSV파일 이름
	CreateCsvFile(&csvFile, fname);
	
	int32 scene_number = ParseToInt(csvFile.Items[iscene][1]);//씬 넘버 저장
	int16 motion = ParseToInt(csvFile.Items[data->SCENE_NUMBER][14]);//효과 넘버 저장
	data->SCENE_NUMBER = scene_number;
	data->MOTION = motion;
	data->STORY_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][15]);//대사 수 저장
	data->CHOICE_NUMBER = ParseToInt(csvFile.Items[data->SCENE_NUMBER][16]);//선택지 수 저장
	data->FONT_SIZE = 30;// 폰트 사이즈 저장
	data->TIMER = 0.0f;//타이머 초기화
	data->VOLUME = 1.0f;//소리 크기 저장
	data->EARTH = 0.0f;//지진 타이머
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
	
	for (int i = 0; i < 5; i++)//카운터 초기화
	{
		data->CHOICE_COUNT[i] = 0;
	}
	char* ttes1 = ParseToUnicode(csvFile.Items[data->SCENE_NUMBER][2]);// 스토리 저장
	char* ttes2 = ttes1;
	SafeFree(ttes1);
	for (int i = 0; i < data->STORY_NUMBER; i++)// 스토리 가공
	{
		wchar_t* str2[100] = { L"" };
		ttes2 = StringLine(ttes2, str2);
		Text_CreateText(&data->STORY[i], "Chun_Bold.ttf", data->FONT_SIZE, str2, wcslen(str2));
	}
	
	if (iscene != 0)
	{
		for (int i = 0; i < wav_s; i++)// 사운드 데이터에 추가
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
		for (int i = 0; i < data->CHOICE_NUMBER; i++)//선택지 수만큼 각자 대사,이동씬,음악 저장
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
	Image_LoadImage(&data->IMAGE, imageFile);// 이미지 저장 
	char imageFile1[128] = "7.png";
	Image_LoadImage(&data->STORY_IMAGE, imageFile1);// 창 화면 이미지 저장
	//SafeFree(imageFile2);
	if (data->MOTION == 1 || data->MOTION == 2)
	{
		char imageFile2[128] = "BLACK.png";
		Image_LoadImage(&data->BLACK_IMAGE, imageFile2);// 검은 화면 이미지 저장
	}
	SafeFree(imageFile);
	Audio_Play(&data->SOUND, 1);
	FreeCsvFile(&csvFile);//파일 닫기
}

void update_main(void)
{
	if (iscene == 0)//0번씬 타이틀로 이동
	{
		Scene_SetNextScene(SCENE_TITLE);
		iscene = 1;
	}

	if (iscene == 118)//118번씬 엔딩으로 이동
	{
		Scene_SetNextScene(SCENE_END);
		iscene = 1;
	}
	MainSceneData* data = (MainSceneData*)g_Scene.Data;
	if (iscene ==4)
	{
		Audio_StopSoundEffect();
	}
	data->TIMER += Timer_GetDeltaTime();//시간초 받기
	data->EARTH += Timer_GetDeltaTime();//시간초 받기
	data->NEXT += Timer_GetDeltaTime();//시간초 받기

	if (data->MOTION > 0)
	{
		switch (data->MOTION)
		{
		case 1://명전
			data->Alpha = Clamp(0, data->Alpha - 1, 255);
			break;
		case 3://지진 효과

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
	if (wav_t != 0)//소리 출력
	{
		
		if (iscene < 80)
		{
			Audio_StopSoundEffect();
		}

		switch (wav_t)
		{
		case 1:
			Audio_PlaySoundEffect(&C_SOUND[0], 1);//선택지 1
			wav_t = 0;
			break;
		case 2:Audio_PlaySoundEffect(&C_SOUND[1], 1);//선택지 2
			wav_t = 0;
			break;
		case 3:Audio_PlaySoundEffect(&C_SOUND[2], 1);//선택지 3
			wav_t = 0;
			break;
		default:
			break;
		}
	}

	if (data->CHOICE_COUNT[1] < data->STORY_NUMBER)
	{
		if (Input_GetKeyDown(VK_SPACE))//글자 스킵 기능
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
		if (Input_GetKeyDown(VK_SPACE))//선택지가 나온 상태에서 스페이스 바를 누를 때 이동
		{
			switch (data->CHOICE_COUNT[0])
			{
			case 0:iscene = data->CHOICE_MOVE[0];
				Audio_Stop();
				wav_t = 1;
				if (data->MOTION == 2)//암전 만들기
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
				if (data->MOTION == 2)//암전 만들기
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
				if (data->MOTION == 2)//암전 만들기
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

	if (data->TIMER >= 1.0f && data->CHOICE_COUNT[1] <= data->STORY_NUMBER)//대화창 카운터
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
	
	SDL_Color color1 = {.r = 255, .g = 255, .b = 255, .a = 255};//글씨 색
	SDL_Color color2 = {.r = 255, .g = 255, .b = 255, .a = 255};//선택지 글씨 색(선택)
	SDL_Color color3 = {.r = 255, .g = 255, .b = 0, .a = 255};//선택지 글씨 색(비 선택)


	for (int i = 0; i < data->CHOICE_COUNT[1]; i++)//대사 출력
	{
		Renderer_DrawTextBlended(&data->STORY[i], 50, 50 + i * (data->FONT_SIZE * 1.5), color1);
	}
	if (data->CHOICE_COUNT[1] > data->STORY_NUMBER && data->CHOICE_NUMBER != 0)
	{
		for (int i = 0; i < data->CHOICE_NUMBER; i++)//선택지 출력
		{
			if (data->CHOICE_COUNT[0] == i)
			{
				Renderer_DrawTextBlended(&data->CHOICE[i], 50, 450 + i * (data->FONT_SIZE * 2), color3);
			}
			else
			{
				Renderer_DrawTextBlended(&data->CHOICE[i], 50, 450 + i * (data->FONT_SIZE * 2), color2);
			}
			data->CHOICE_COUNT[2] = 1;//선택지가 출력되지 않으면 넘어가지 않게 카운트
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
	Text_CreateText(&data->EndingText2, "d2coding.ttf", 40, L"테스다훈과 함께", 8);

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

		switch (data->Count) // 특정 위치마다 초기화 및 텍스트 바뀜
		{
		case 1:
			Text_CreateText(&data->EndingText, "d2coding.ttf", 40, L"팀장: 장형규, 이다훈", 12);
			break;
		case 3:
			Text_CreateText(&data->EndingText, "d2coding.ttf", 40, L"팀원: 홍종혁, 최재연", 12);
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

		switch (data->Count)// 특정 위치마다 초기화 및 텍스트 바뀜 두번째,
		{
		case 2:
			Text_CreateText(&data->EndingText2, "d2coding.ttf", 40, L"팀원: 권선혁, 신혁진", 12);
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

	if (data->Alpha >= 200) // 알파값이 200되면 움직임
	{
		data->Y = data->Y - data->Speed;

		data->Alpha2 = data->Alpha2 + 1;
		data->Y2 = data->Y2 - data->Speed;
	}

	if (data->Alpha2 > 255)
	{
		data->Alpha2 = 255;
	}

	if (Input_GetKeyDown(VK_SPACE)) // 속도조절
	{
		data->Speed = 3;
	}

	if (Input_GetKeyUp(VK_SPACE))
	{
		data->Speed = 1;
	}

	if (Input_GetKeyUp(VK_ESCAPE))// 뒤로가기
	{
		Scene_SetNextScene(SCENE_TITLE);
		Audio_Stop();
	}

}
void render_end(void)
{

	EndingSceneNewData* data = (EndingSceneNewData*)g_Scene.Data;
	SDL_Color TextColor = { .r = 255, .g = 255, .b = 255, .a = data->Alpha };//글씨 색
	SDL_Color TextColor2 = { .r = data->R - (rand() * 2), .g = data->G - (rand() * 2), .b = data->B - (rand() * 2), .a = data->Alpha2 };//글씨 색
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