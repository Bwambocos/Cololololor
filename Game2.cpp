// include
#include "Game2.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

// define
#define LEVEL_MAX 10
#define STAGE_MAX 5

// グローバル変数
struct Color_t
{
	int red, green, blue;
};
unsigned ColorToDxColor_G1(Color_t c)
{
	return GetColor(c.red, c.green, c.blue);
}
struct ball	// 球1つ
{
	Color_t color[LEVEL_MAX * 5];
	int pos_x, pos_y;
};
struct problem
{
	ball ColorBall;
	int ans;
};

problem Color_data[STAGE_MAX];
int G_Main = -1;
int S_BGM;
int F_Main;
int Score_num, Stage_num, Level_num;

// 初期化（一回のみ）
void Game2_Init1()
{
	Score_num = 0, Stage_num = 0, Level_num = 1;
	for (int i = 0; i < STAGE_MAX; ++i)
	{
		for (int j = 0; j < Level_num * 5; ++j)
		{
			Color_data[i].ColorBall.color[j].red = GetRand(255);
			Color_data[i].ColorBall.color[j].green = GetRand(255);
			Color_data[i].ColorBall.color[j].blue = GetRand(255);
		}
		Color_data[i].ans = GetRand((Level_num * 5) - 1);
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
	if (Stage_num >= STAGE_MAX)
	{
		++Level_num, Stage_num = 0;
		if (Level_num >= LEVEL_MAX) { Level_num = 1; }
		Game2_Init1();
	}
}

// 更新
void Game2_Update()
{

}

// 描画
void Game2_Draw()
{
	// 画像
	DrawGraph(0, 0, G_Main, TRUE);

	// 文字
	DrawFormatStringToHandle(45, 410, GetColor(0, 0, 0), F_Main, "LEVEL %d", Level_num);
	DrawFormatStringToHandle(450, 410, GetColor(0, 0, 0), F_Main, "STAGE %d", Stage_num);
}