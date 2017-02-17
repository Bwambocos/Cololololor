// include
#include "Game2.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"

// define
#define LEVEL_MAX 10
#define STAGE_MAX 5

// �O���[�o���ϐ�
struct Color_t
{
	int red, green, blue;
};
unsigned ColorToDxColor_G1(Color_t c)
{
	return GetColor(c.red, c.green, c.blue);
}
struct ball	// ��1��
{
	Color_t color;
	int pos_x, pos_y;
};

ball ColorBall[LEVEL_MAX * 5];
int G_Main;
int S_BGM;
int F_Main;
int Score_num, Stage_num, Level_num;
int ansBall;

// �������i���̂݁j
void Game2_Init1()
{
	Score_num = 0, Stage_num = 0, Level_num = 1;
	G_Main = LoadGraph("data\\graph\\Game2_Main.png");
	S_BGM = LoadSoundMem("data\\sound\\bgm.mp3");
	F_Main = CreateFontToHandle("Meiryo UI", 32, 5, DX_FONTTYPE_ANTIALIASING_8X8);
}

// �������i����j
void Game2_Init2()
{
	++Stage_num;
	if (Stage_num >= STAGE_MAX)
	{
		++Level_num, Stage_num = 0;
		if (Level_num >= LEVEL_MAX) { Level_num = 1; }
	}
}

// �X�V
void Game2_Update()
{

}

// �`��
void Game2_Draw()
{
	// �摜
	DrawGraph(0, 0, G_Main, TRUE);

	// ����
	DrawFormatStringToHandle(45, 410, GetColor(0, 0, 0), F_Main, "LEVEL %d", Level_num);
	DrawFormatStringToHandle(450, 410, GetColor(0, 0, 0), F_Main, "STAGE %d", Stage_num);
}