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
	Color_t color;
	int pos_x, pos_y;
};

ball ColorBall[LEVEL_MAX * 5];
int G_Main;
int S_BGM;
int ansBall;

// 初期化（一回のみ）
void Game2_Init1()
{
	G_Main = LoadGraph("data\\graph\\Game2_Main.png");
	S_BGM = LoadSoundMem("data\\sound\\bgm.mp3");
}

// 初期化（毎回）
void Game2_Init2()
{

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
}