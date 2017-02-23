// include
#include "Game2.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

// define
#define LEVEL_MAX 10
#define STAGE_MAX 5
#define BALL_NUM  3

// 構造体
struct Color_t
{
	int red, green, blue;
};
unsigned ColorToDxColor(Color_t c)
{
	return GetColor(c.red, c.green, c.blue);
}
struct ball
{
	Color_t color;
	int pos_x, pos_y;
	int def_x, def_y;
};
struct problem
{
	ball ColorBall[LEVEL_MAX * BALL_NUM];
	int ans;
};

// 定数
static const int BALL_MOVE_COST = 10000;		// 何ミリ秒かけて色玉を中心へ移動させるか

// 変数
problem Color_data[STAGE_MAX];
int G_Main = -1;
int S_BGM;
int F_Main;
int g_starttime, g_lasttime;
int Score_num, Stage_num, Level_num = 1;

// 初期化（一回のみ）
void Game2_Init1()
{
	Score_num = 0;
	for (int i = 0; i < STAGE_MAX; ++i)
	{
		for (int j = 0; j < Level_num * BALL_NUM; ++j)
		{
			Color_data[i].ColorBall[j].color.red = GetRand(255);
			Color_data[i].ColorBall[j].color.green = GetRand(255);
			Color_data[i].ColorBall[j].color.blue = GetRand(255);
			switch (j % 4)
			{
			case 1:
				Color_data[i].ColorBall[j].pos_x = GetRand(640);
				Color_data[i].ColorBall[j].pos_y = 0;
				break;
			case 2:
				Color_data[i].ColorBall[j].pos_x = GetRand(640);
				Color_data[i].ColorBall[j].pos_y = 480;
				break;
			case 3:
				Color_data[i].ColorBall[j].pos_x = 0;
				Color_data[i].ColorBall[j].pos_y = GetRand(480);
				break;
			case 0:
				Color_data[i].ColorBall[j].pos_x = 640;
				Color_data[i].ColorBall[j].pos_y = GetRand(480);
				break;
			}
			Color_data[i].ColorBall[j].def_x = Color_data[i].ColorBall[j].pos_x;
			Color_data[i].ColorBall[j].def_y = Color_data[i].ColorBall[j].pos_y;
		}
		Color_data[i].ans = GetRand((Level_num * BALL_NUM) - 1);
	}

	if (G_Main == -1)
	{
		G_Main = LoadGraph("data\\graph\\Game2_Main.png");
		S_BGM = LoadSoundMem("data\\sound\\bgm.mp3");
		F_Main = CreateFontToHandle("Meiryo UI", 32, 5, DX_FONTTYPE_ANTIALIASING_8X8);
	}
}

// 初期化（毎回）
void Game2_Init2()
{
	++Stage_num;
	if (Stage_num > STAGE_MAX)
	{
		++Level_num, Stage_num = 1;
		if (Level_num > LEVEL_MAX) { Level_num = 1; }
		Game2_Init1();
	}
	g_starttime = GetNowCount();
}

// 更新
void Game2_Update()
{
	g_lasttime = GetNowCount();
	for (int i = 0; i < Level_num * BALL_NUM; ++i)
	{
		if (Color_data[Stage_num - 1].ColorBall[i].pos_x <= 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y <= 240)	// 左上
		{
			Color_data[Stage_num - 1].ColorBall[i].pos_x += 1;
			Color_data[Stage_num - 1].ColorBall[i].pos_y += 1;
		}
		if (Color_data[Stage_num - 1].ColorBall[i].pos_x > 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y <= 240)	// 右上
		{
			Color_data[Stage_num - 1].ColorBall[i].pos_x -= 1;
			Color_data[Stage_num - 1].ColorBall[i].pos_y += 1;
		}
		if (Color_data[Stage_num - 1].ColorBall[i].pos_x <= 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y > 240)	// 左下
		{
			Color_data[Stage_num - 1].ColorBall[i].pos_x += 1;
			Color_data[Stage_num - 1].ColorBall[i].pos_y -= 1;
		}
		if (Color_data[Stage_num - 1].ColorBall[i].pos_x > 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y > 240)	// 右下
		{
			Color_data[Stage_num - 1].ColorBall[i].pos_x -= 1;
			Color_data[Stage_num - 1].ColorBall[i].pos_y -= 1;
		}
	}

#ifdef _DEBUG
	if (Keyboard_Get(KEY_INPUT_ESCAPE) == 1)
	{
		SceneMgr_ChangeScene(Scene_Game2);
	}
#endif
}

// 描画
void Game2_Draw()
{
	// 画像
	DrawGraph(0, 0, G_Main, TRUE);

	// 文字
	DrawFormatStringToHandle(45, 410, GetColor(0, 0, 0), F_Main, "LEVEL %d", Level_num);
	DrawFormatStringToHandle(450, 410, GetColor(0, 0, 0), F_Main, "STAGE %d", Stage_num);

	// 色玉
	for (int i = 0; i < Level_num * BALL_NUM; ++i)
	{
		DrawCircle(Color_data[Stage_num - 1].ColorBall[i].pos_x, Color_data[Stage_num - 1].ColorBall[i].pos_y, 15, ColorToDxColor(Color_data[Stage_num - 1].ColorBall[i].color), TRUE);
		DrawCircle(Color_data[Stage_num - 1].ColorBall[i].pos_x, Color_data[Stage_num - 1].ColorBall[i].pos_y, 15, GetColor(255, 255, 255), FALSE, 2);
		if (i == Color_data[Stage_num - 1].ans)
		{
			DrawRoundRect(285, 380, 355, 450, 15, 15, ColorToDxColor(Color_data[Stage_num - 1].ColorBall[i].color), TRUE);
		}
	}
}