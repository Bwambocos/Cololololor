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
typedef struct ball_t	// ��1��
{
	Color_t color;
	int pos_x, pos_y;
}ball;

ball ColorBall[LEVEL_MAX * 5];
int G_Main;
int S_BGM;
int ansBall;

// �������i���̂݁j
void Game2_Init1()
{

}

// �������i����j
void Game2_Init2()
{

}

// �X�V
void Game2_Update()
{

}

// �`��
void Game2_Draw()
{

}