// include
#include <vector>
#include <algorithm>
#include "Game2.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Mouse.h"

// define
#define LEVEL_MAX 10
#define STAGE_MAX 5
#define BALL_NUM  3
#define BALL_R	  15
#define BALL_MIN_DISTANCE BALL_R * 2

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
	double pos_x, pos_y;
	double def_x, def_y;
	bool mouse_in = false;
};
struct problem
{
	ball ColorBall[LEVEL_MAX * BALL_NUM];
	std::vector<int>Ball_posx_list, Ball_posy_list;
	int ans;
};

// 定数
static const int BALL_MOVE_COST = 225;

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
				while(true)
				{
					Color_data[i].ColorBall[j].pos_x = GetRand(640);
					if (Color_data[i].Ball_posx_list.size() > 0)
					{
						if (Check_Overlap(Color_data[i].Ball_posx_list.begin(), Color_data[i].Ball_posx_list.end(), (int)Color_data[i].ColorBall[j].pos_x) == false)
						{
							Color_data[i].Ball_posx_list.push_back((int)Color_data[i].ColorBall[j].pos_x);
							break;
						}
					}
					else
					{
						Color_data[i].Ball_posx_list.push_back((int)Color_data[i].ColorBall[j].pos_x);
						break;
					}
				}
				Color_data[i].ColorBall[j].pos_y = 0;
				break;
			case 2:
				while (true)
				{
					Color_data[i].ColorBall[j].pos_x = GetRand(640);
					if (Color_data[i].Ball_posx_list.size() > 0)
					{
						if (Check_Overlap(Color_data[i].Ball_posx_list.begin(), Color_data[i].Ball_posx_list.end(), (int)Color_data[i].ColorBall[j].pos_x) == false)
						{
							Color_data[i].Ball_posx_list.push_back((int)Color_data[i].ColorBall[j].pos_x);
							break;
						}
					}
					else
					{
						Color_data[i].Ball_posx_list.push_back((int)Color_data[i].ColorBall[j].pos_x);
						break;
					}
				}
				Color_data[i].ColorBall[j].pos_y = 480;
				break;
			case 3:
				Color_data[i].ColorBall[j].pos_x = 0;
				while (true)
				{
					Color_data[i].ColorBall[j].pos_y = GetRand(640);
					if (Color_data[i].Ball_posy_list.size() > 0)
					{
						if (Check_Overlap(Color_data[i].Ball_posy_list.begin(), Color_data[i].Ball_posy_list.end(), (int)Color_data[i].ColorBall[j].pos_y) == false)
						{
							Color_data[i].Ball_posy_list.push_back((int)Color_data[i].ColorBall[j].pos_y);
							break;
						}
					}
					else
					{
						Color_data[i].Ball_posy_list.push_back((int)Color_data[i].ColorBall[j].pos_y);
						break;
					}
				}
				break;
			case 0:
				Color_data[i].ColorBall[j].pos_x = 640;
				while (true)
				{
					Color_data[i].ColorBall[j].pos_y = GetRand(640);
					if (Color_data[i].Ball_posy_list.size() > 0)
					{
						if (Check_Overlap(Color_data[i].Ball_posy_list.begin(), Color_data[i].Ball_posy_list.end(), (int)Color_data[i].ColorBall[j].pos_y) == false)
						{
							Color_data[i].Ball_posy_list.push_back((int)Color_data[i].ColorBall[j].pos_y);
							break;
						}
					}
					else
					{
						Color_data[i].Ball_posy_list.push_back((int)Color_data[i].ColorBall[j].pos_y);
						break;
					}
				}
				break;
			}
			Color_data[i].ColorBall[j].def_x = Color_data[i].ColorBall[j].pos_x;
			Color_data[i].ColorBall[j].def_y = Color_data[i].ColorBall[j].pos_y;
		}
		Color_data[i].Ball_posx_list.erase(Color_data[i].Ball_posx_list.begin(), Color_data[i].Ball_posx_list.end());
		Color_data[i].Ball_posy_list.erase(Color_data[i].Ball_posy_list.begin(), Color_data[i].Ball_posy_list.end());
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
		if (Level_num > LEVEL_MAX)
		{
			Level_num = 1;
		}
		Game2_Init1();
	}
	g_starttime = GetNowCount();
}

// 更新
void Game2_Update()
{
	g_lasttime = GetNowCount();
	if ((g_lasttime - g_starttime) >= BALL_MOVE_COST * 40)
	{
		SceneMgr_ChangeScene(Scene_Game2);
	}

	// 色玉
	for (int i = 0; i < Level_num * BALL_NUM; ++i)
	{
		double move_x = (Color_data[Stage_num - 1].ColorBall[i].def_x - 320) / BALL_MOVE_COST;
		double move_y = (Color_data[Stage_num - 1].ColorBall[i].def_y - 240) / BALL_MOVE_COST;

		// クリック判定
		{
			if (CheckMouseClick((int)Color_data[Stage_num - 1].ColorBall[i].pos_x - BALL_R, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y - BALL_R,
				(int)Color_data[Stage_num - 1].ColorBall[i].pos_x + BALL_R, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y + BALL_R) == true)
			{
				if (i == Color_data[Stage_num - 1].ans)
				{
					Score_num += ((BALL_MOVE_COST * 40) - (g_lasttime - g_starttime));
					SceneMgr_ChangeScene(Scene_Game2);
				}
			}
			if (CheckMouseIn((int)Color_data[Stage_num - 1].ColorBall[i].pos_x - BALL_R, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y - BALL_R,
				(int)Color_data[Stage_num - 1].ColorBall[i].pos_x + BALL_R, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y + BALL_R) == true)
			{
				Color_data[Stage_num - 1].ColorBall[i].mouse_in = true;
			}
			else
			{
				Color_data[Stage_num - 1].ColorBall[i].mouse_in = false;
			}
		}

		// 座標更新
		{
			if (Color_data[Stage_num - 1].ColorBall[i].pos_x <= 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y <= 240)	// 左上
			{
				Color_data[Stage_num - 1].ColorBall[i].pos_x -= move_x;
				Color_data[Stage_num - 1].ColorBall[i].pos_y -= move_y;
			}
			if (Color_data[Stage_num - 1].ColorBall[i].pos_x > 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y <= 240)	// 右上
			{
				Color_data[Stage_num - 1].ColorBall[i].pos_x -= move_x;
				Color_data[Stage_num - 1].ColorBall[i].pos_y -= move_y;
			}
			if (Color_data[Stage_num - 1].ColorBall[i].pos_x <= 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y > 240)	// 左下
			{
				Color_data[Stage_num - 1].ColorBall[i].pos_x -= move_x;
				Color_data[Stage_num - 1].ColorBall[i].pos_y -= move_y;
			}
			if (Color_data[Stage_num - 1].ColorBall[i].pos_x > 320 && Color_data[Stage_num - 1].ColorBall[i].pos_y > 240)	// 右下
			{
				Color_data[Stage_num - 1].ColorBall[i].pos_x -= move_x;
				Color_data[Stage_num - 1].ColorBall[i].pos_y -= move_y;
			}
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
	// 色玉
	for (int i = 0; i < Level_num * BALL_NUM; ++i)
	{
		DrawCircle((int)Color_data[Stage_num - 1].ColorBall[i].pos_x, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y, BALL_R, ColorToDxColor(Color_data[Stage_num - 1].ColorBall[i].color), TRUE);
		if (Color_data[Stage_num - 1].ColorBall[i].mouse_in == true)
		{
			DrawCircle((int)Color_data[Stage_num - 1].ColorBall[i].pos_x, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y, BALL_R, GetColor(255, 255, 0), FALSE, 2);
		}
		else
		{
			DrawCircle((int)Color_data[Stage_num - 1].ColorBall[i].pos_x, (int)Color_data[Stage_num - 1].ColorBall[i].pos_y, BALL_R, GetColor(255, 255, 255), FALSE, 2);
		}
	}

	// 画像
	DrawGraph(0, 0, G_Main, TRUE);

	// ステータス
	DrawFormatStringToHandle(45, 410, GetColor(0, 0, 0), F_Main, "LEVEL %d", Level_num);
	DrawFormatStringToHandle(450, 410, GetColor(0, 0, 0), F_Main, "STAGE %d", Stage_num);
	DrawRoundRect(285, 380, 355, 450, 15, 15, ColorToDxColor(Color_data[Stage_num - 1].ColorBall[Color_data[Stage_num - 1].ans].color), TRUE);

	clsDx();
	printfDx("%d\n", Score_num);
}

bool Check_Overlap(std::vector<int>::iterator begin,
	std::vector<int>::iterator end,
	int num)
{
	std::vector<int>tmp(begin, end);
	std::copy(begin, end, tmp.begin());
	std::sort(tmp.begin(), tmp.end());
	auto min = std::lower_bound(tmp.begin(), tmp.end(), num - BALL_MIN_DISTANCE);
	auto max = std::lower_bound(tmp.begin(), tmp.end(), num + BALL_MIN_DISTANCE);
	if (min == tmp.end()) { min = tmp.end() - 1; }
	if (max == tmp.end()) { max = tmp.end() - 1; }
	if (abs(*min - num) > BALL_MIN_DISTANCE && abs(*max - num) > BALL_MIN_DISTANCE)
	{
		return false;
	}
	return true;
}