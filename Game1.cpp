#include "Game1.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <math.h>
#define LEVEL_MAX	10
#define STAGE_MAX	10
using namespace std;

// グローバル変数
struct Color_t_G1
{
	int red, green, blue;
};
unsigned ColorToDxColor_G1(Color_t_G1 c)
{
	return GetColor(c.red, c.green, c.blue);
}
typedef struct problem_G1
{
	int Total;
	Color_t_G1 Color[LEVEL_MAX * LEVEL_MAX];
	int Ans;
}problem_data_G1;

problem_data_G1 Color_data_G1[STAGE_MAX];
FILE *fp_G1;
int Score_num_G1 = 0;
int Total_num_G1;
int Total_sqrt_G1;
int Stage_num_G1 = -1;
int Level_num_G1 = 1;
int Starttime_G1;
double Time_num_G1 = 0;
int Mouse_memo_G1;
int Mouse_XY_G1[LEVEL_MAX * LEVEL_MAX][2] = { 0 };
int Fonthandle_G1 = -1;
int G_Main_G1 = -1;
int S_right_G1 = -1;
int S_BGM_G1 = -1;
char Filename_G1[50] = { '\0' };
int CorO_flag_G1;

// 初期化（一回のみ）
void Game1_Init1()
{
	Score_num_G1 = 0;
	for (int i = 0; i < STAGE_MAX; i++)
	{
		for (int j = 0; j < (Level_num_G1 + 1) * (Level_num_G1 + 1); j++)
		{
			Color_data_G1[i].Color[j].red = GetRand(255);
			Color_data_G1[i].Color[j].green = GetRand(255);
			Color_data_G1[i].Color[j].blue = GetRand(255);
		}
		Color_data_G1[i].Total = (Level_num_G1 + 1) * (Level_num_G1 + 1);
		Color_data_G1[i].Ans = GetRand(((Level_num_G1 + 1) * (Level_num_G1 + 1)) - 1);
	}

	if (G_Main_G1 == -1)
	{
		G_Main_G1 = LoadGraph("data\\graph\\Game1_Main.png");
		S_right_G1 = LoadSoundMem("data\\sound\\next.wav");
		S_BGM_G1 = LoadSoundMem("data\\sound\\bgm.mp3");
		Fonthandle_G1 = CreateFontToHandle("Meiryo UI", 32, 5, DX_FONTTYPE_ANTIALIASING_8X8);
	}
	
	PlaySoundMem(S_BGM_G1, DX_PLAYTYPE_BACK, FALSE);
}

// 初期化（毎回）
void Game1_Init2()
{
	Stage_num_G1++;
	if (Stage_num_G1 > STAGE_MAX - 1)
	{
		Level_num_G1++;
		Stage_num_G1 = 0;
		if (Level_num_G1 > LEVEL_MAX - 1) { Level_num_G1 = 1; }
		Game1_Init1();
	}
	Total_sqrt_G1 = (int)sqrt(Color_data_G1[Stage_num_G1].Total);
	Mouse_memo_G1 = 230 / Total_sqrt_G1;
	for (int i = 0; i < Color_data_G1[Stage_num_G1].Total; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (j == 0){ Mouse_XY_G1[i][j] = 210 + (i % Total_sqrt_G1) * Mouse_memo_G1; }
			if (j == 1){ Mouse_XY_G1[i][j] = 100 + (i / Total_sqrt_G1) * Mouse_memo_G1; }
		}
	}
	Starttime_G1 = GetNowCount();
}

// 更新
void Game1_Update()
{
	Time_num_G1 = (GetNowCount() - Starttime_G1) / 100;
	if ((100 - Time_num_G1) / 10 <= 0)
	{
		CorO_flag_G1 = -1;
		Level_num_G1--;
		Stage_num_G1 = STAGE_MAX - 1;
		SceneMgr_ChangeScene(Scene_Result);
	}
	if ((CheckMouseClick(Mouse_XY_G1[Color_data_G1[Stage_num_G1].Ans][0], Mouse_XY_G1[Color_data_G1[Stage_num_G1].Ans][1], Mouse_XY_G1[Color_data_G1[Stage_num_G1].Ans][0] + Mouse_memo_G1, Mouse_XY_G1[Color_data_G1[Stage_num_G1].Ans][1] + Mouse_memo_G1)) == true)
	{
		if (Stage_num_G1 == STAGE_MAX - 1)
		{
			StopSoundMem(S_BGM_G1);
			PlaySoundMem(S_right_G1, DX_PLAYTYPE_BACK);
			CorO_flag_G1 = 0;
			SceneMgr_ChangeScene(Scene_Result);
		}
		else
		{
			PlaySoundMem(S_right_G1, DX_PLAYTYPE_BACK);
			SceneMgr_ChangeScene(Scene_Game1);
		}
		Score_num_G1 += (100 - (int)Time_num_G1) * 100;
	}

#ifdef _DEBUG
	if (Keyboard_Get(KEY_INPUT_DELETE) != 0)
	{
		if (Stage_num_G1 == STAGE_MAX - 1)
		{
			StopSoundMem(S_BGM_G1);
			PlaySoundMem(S_right_G1, DX_PLAYTYPE_BACK);
			CorO_flag_G1 = 0;
			SceneMgr_ChangeScene(Scene_Result);
		}
		else
		{
			PlaySoundMem(S_right_G1, DX_PLAYTYPE_BACK);
			SceneMgr_ChangeScene(Scene_Game1);
		}
	}
#endif
}

// 描画
void Game1_Draw()
{
	DrawGraph(0, 0, G_Main_G1, TRUE);
	DrawFormatStringToHandle(45, 410, GetColor(0, 0, 0), Fonthandle_G1, "LEVEL %d", Level_num_G1);
	DrawFormatStringToHandle(435, 410, GetColor(0, 0, 0), Fonthandle_G1, "残り時間:%f", (100 - Time_num_G1) / 10);
	for (int i = 0; i < Color_data_G1[Stage_num_G1].Total; i++)
	{
		DrawRoundRect(Mouse_XY_G1[i][0], Mouse_XY_G1[i][1], Mouse_XY_G1[i][0] + Mouse_memo_G1, Mouse_XY_G1[i][1] + Mouse_memo_G1, 15, 15, ColorToDxColor_G1(Color_data_G1[Stage_num_G1].Color[i]), TRUE);
		if (i == Color_data_G1[Stage_num_G1].Ans) { DrawRoundRect(285, 380, 355, 450, 15, 15, ColorToDxColor_G1(Color_data_G1[Stage_num_G1].Color[i]), TRUE); }
	}
}

// ClearかOverか返す
int getCorO_G1()
{
	return CorO_flag_G1;
}

// Scoreを返す
int getScore_G1()
{
	return Score_num_G1;
}

// Levelを返す
int getLevel_G1()
{
	return Level_num_G1;
}