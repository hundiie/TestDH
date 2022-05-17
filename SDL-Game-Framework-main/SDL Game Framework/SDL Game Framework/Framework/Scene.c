#include "stdafx.h"
#include "Scene.h"
#include "Text.h"

#include "Framework.h"

Scene g_Scene;

static ESceneType s_nextScene = SCENE_NULL;

#pragma region TitleScene

#define SOLID 0
#define SHADED 1
#define BLENDED 2

const wchar_t* str[] = {
	L"게임 시작",
	L"게임 종료",

	/*L"B키를 누르면 폰트가 굵게 변합니다.",
	L"I키를 누르면 폰트가 이탤릭체로 변합니다.",
	L"U키를 누르면 텍스트에 밑줄이 생깁니다.",
	L"S키를 누르면 텍스트에 취소선이 생깁니다.",
	L"N키를 누르면 다시 원래대로 돌아옵니다.",
	L"C키를 누르면 렌더 모드가 바뀝니다. (Solid -> Shaded -> Blended)",
	L"1키를 누르면 텍스트가 작아집니다.",
	L"2키를 누르면 텍스트가 커집니다.",
	L"스페이스 키를 누르면 다음 씬으로 넘어갑니다."*/
};
#define TEXT_NUM1 2

typedef struct TitleSceneData
{
	Text	GuideLine[TEXT_NUM1];
	COORD	coord;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
	int32		X;
	int32		Y;
} TitleSceneData;

void init_title(void)
{
	g_Scene.Data = malloc(sizeof(TitleSceneData));
	memset(g_Scene.Data, 0, sizeof(TitleSceneData));

	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->FontSize = 40;
	for (int32 i = 0; i < TEXT_NUM1; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", data->FontSize, str[i], wcslen(str[i]));
	}
	data->coord.X = 10;
	data->coord.Y = 10;
	data->RenderMode = SOLID;
	int32		X=10;
	int32		Y=10;
	Image_LoadImage(&data->TestImage, "Background.jfif");
	CSV;
}

int count = 0;
void update_title(void)
{
	
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	
	if (count > 0)
	{
		if (Input_GetKeyDown(VK_UP))
		{
			count--;
		}
	}
	if (count < TEXT_NUM1 - 1)
	{
		if (Input_GetKeyDown(VK_DOWN))
		{
			count++;
		}
	}
	if (Input_GetKeyDown('R'))
	{
		Scene_SetNextScene(SCENE_MAIN);
	}
}

void render_title(void)
{
	TitleSceneData* data = (TitleSceneData*)g_Scene.Data;
	data->X = rand()% 1020;
	data->Y = rand()% 200;

	SDL_Color color = { .a = 255 };
	SDL_Color choice_color = { .g = 255 };
	
	Renderer_DrawImage(&data->TestImage, data->X, data->Y);
	
	for (int32 i = 0; i < TEXT_NUM1; ++i)
	{
		Renderer_DrawTextSolid(&data->GuideLine[i], 500, 500 + i* data->FontSize, color);
		Renderer_DrawTextSolid(&data->GuideLine[count], 500, 500 + count* data->FontSize, choice_color);
	}
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

#pragma region MainScene
const wchar_t* st[] = {
	L"여기서는 사운드와 이미지 블렌딩에 대해서 알아봅시다.",
	L"화살표키로 이미지를 이동시킬 수 있습니다.",
	L"E키를 누르면 이펙트를 재생시킬 수 있습니다. 이펙트 소리가 작으니 볼륨을 낮춘 후 진행하세요.",
	L"M키로 음악을 끄거나 켤 수 있습니다.",
	L"P키로 음악을 멈추거나 재개할 수 있습니다.",
	L"1번과 2번으로 볼륨을 조절할 수 있습니다.",
	L"WASD로 이미지의 스케일을 조정할 수 있습니다.",
	L"KL키로 이미지의 투명도를 조절할 수 있습니다."
};

#define GUIDELINE_COUNT 8

typedef struct MainSceneData
{
	Text		GuideLine[GUIDELINE_COUNT];
	Music		BGM;
	float		Volume;
	SoundEffect Effect;
	Image		BackGround;
	float		Speed;
	int32		X;
	int32		Y;
	int32		Alpha;
} MainSceneData;

void logOnFinished(void)
{
	LogInfo("You can show this log on stopped the music");
}

void log2OnFinished(int32 channel)
{
	LogInfo("You can show this log on stopped the effect");
}

void init_main(void)
{
	g_Scene.Data = malloc(sizeof(MainSceneData));
	memset(g_Scene.Data, 0, sizeof(MainSceneData));

	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 16, st[i], wcslen(st[i]));
	}
	
	Image_LoadImage(&data->BackGround, "background.jfif");

	Audio_LoadMusic(&data->BGM, "powerful.mp3");
	Audio_HookMusicFinished(logOnFinished);
	Audio_LoadSoundEffect(&data->Effect, "effect2.wav");
	Audio_HookSoundEffectFinished(log2OnFinished);
	Audio_PlayFadeIn(&data->BGM, INFINITY_LOOP, 3000);

	data->Volume = 1.0f;

	data->Speed = 400.0f;
	data->X = 400;
	data->Y = 400;
	data->Alpha = 255;
}

void update_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	if (Input_GetKeyDown('E'))
	{
		Audio_PlaySoundEffect(&data->Effect, 1);
	}

	if (Input_GetKeyDown('M'))
	{
		if (Audio_IsMusicPlaying())
		{
			Audio_Stop();
		}
		else
		{
			Audio_Play(&data->BGM, INFINITY_LOOP);
		}
	}

	if (Input_GetKeyDown('P'))
	{
		if (Audio_IsMusicPaused())
		{
			Audio_Resume();
		}
		else
		{
			Audio_Pause();
		}
	}

	if (Input_GetKey('1'))
	{
		data->Volume -= 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey('2'))
	{
		data->Volume += 0.01f;
		Audio_SetVolume(data->Volume);
	}

	if (Input_GetKey(VK_DOWN))
	{
		data->Y += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_UP))
	{
		data->Y -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_LEFT))
	{
		data->X -= data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey(VK_RIGHT))
	{
		data->X += data->Speed * Timer_GetDeltaTime();
	}

	if (Input_GetKey('W'))
	{
		data->BackGround.ScaleY -= 0.05f;
	}

	if (Input_GetKey('S'))
	{
		data->BackGround.ScaleY += 0.05f;
	}

	if (Input_GetKey('A'))
	{
		data->BackGround.ScaleX -= 0.05f;
	}

	if (Input_GetKey('D'))
	{
		data->BackGround.ScaleX += 0.05f;
	}

	if (Input_GetKey('K'))
	{
		data->Alpha = Clamp(0, data->Alpha - 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}

	if (Input_GetKey('L'))
	{
		data->Alpha = Clamp(0, data->Alpha + 1, 255);
		Image_SetAlphaValue(&data->BackGround, data->Alpha);
	}
}

void render_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		SDL_Color color = { .a = 255 };
		Renderer_DrawTextSolid(&data->GuideLine[i], 10, 20 * i, color);
	}

	Renderer_DrawImage(&data->BackGround, data->X, data->Y);
}

void release_main(void)
{
	MainSceneData* data = (MainSceneData*)g_Scene.Data;

	for (int32 i = 0; i < GUIDELINE_COUNT; ++i)
	{
		Text_FreeText(&data->GuideLine[i]);
	}
	Audio_FreeMusic(&data->BGM);
	Audio_FreeSoundEffect(&data->Effect);

	SafeFree(g_Scene.Data);
}
#pragma endregion

#pragma region scene2

#define TEXT_NUM2 2
const wchar_t* str2[] = {
	L"게임 시작",
	L"게임 종료",
};
typedef struct scene2SceneData
{
	Text	GuideLine[TEXT_NUM2];
	COORD	coord;
	int32	FontSize;
	int32	RenderMode;
	Image	TestImage;
}  scene2sceneData;

void init_scene2 (void)
{
	//g_Scene.Data = malloc(sizeof(scene2sceneData));
	//memset(g_Scene.Data, 0, sizeof(scene2sceneData));

	//scene2sceneData* data = (scene2sceneData*)g_Scene.Data;
	//for (int32 i = 0; i < TEXT_NUM2; ++i)
	//{
	//	Text_CreateText(&data->GuideLine[i], "d2coding.ttf", 20, str2[i], wcslen(str2[i]));
	//}
	//data->coord.X = 10;
	//data->coord.Y = 10;
	//data->RenderMode = SOLID;

	//Image_LoadImage(&data->TestImage, "Background.jfif");
}
void update_scene2 (void)
{
	//scene2sceneData* data = (scene2sceneData*)g_Scene.Data;

}
void render_scene2 (void)
{
	//scene2sceneData* data = (scene2sceneData*)g_Scene.Data;

}
void release_scene2(void)
{
	//scene2sceneData* data = (scene2sceneData*)g_Scene.Data;

	//for (int32 i = 0; i < TEXT_NUM2; ++i)
	//{
	//	Text_FreeText(&data->GuideLine[i]);
	//}

	//SafeFree(g_Scene.Data);
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
	case SCENE_SCENE2:
		g_Scene.Init = init_scene2;
		g_Scene.Update = update_scene2;
		g_Scene.Render = render_scene2;
		g_Scene.Release = release_scene2;
		break;
	}

	g_Scene.Init();

	s_nextScene = SCENE_NULL;
}