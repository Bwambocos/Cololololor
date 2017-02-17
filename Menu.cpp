#include "Menu.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Mouse.h"

int Appeal();

// グローバル変数
int G_Main_M;
int G_thum_M[2];
int G_select_M;
int S_select_M;
bool F_frame1_M = false;
bool F_frame2_M = false;
bool F_sound1_M = false;
bool F_sound2_M = false;
int before_M = -1;
int tmp_M = -1;

// 初期化
void Menu_Init()
{
	G_Main_M = LoadGraph("data\\graph\\Menu_Main.png");
	LoadDivGraph("data\\graph\\Menu_thum.png", 2, 2, 1, 240, 240, G_thum_M);
	G_select_M = LoadGraph("data\\graph\\Menu_select.png");
	S_select_M = LoadSoundMem("data\\sound\\select.wav");
}

// 更新
void Menu_Update()
{
	if (CheckMouseIn(30, 150, 270, 360) == true)
	{
		F_frame1_M = true; F_sound1_M = true; before_M = 1;
	}
	if (CheckMouseIn(30, 150, 270, 360) == false)
	{
		F_frame1_M = false; F_sound1_M = false; before_M = -1;
	}
	if (CheckMouseClick(30, 150, 270, 360) == true) { SceneMgr_ChangeScene(Scene_Game1); }
	if (CheckMouseIn(370, 150, 570, 360) == true)
	{
		F_frame2_M = true; F_sound2_M = true; before_M = 2;
	}
	if (CheckMouseIn(370, 150, 610, 360) == false)
	{
		F_frame2_M = false; F_sound2_M = false; before_M = -1;
	}
	if (CheckMouseClick(370, 150, 610, 360) == true) { Appeal(); }
	if (F_sound1_M == true || F_sound2_M == true)
	{
		if (before_M != tmp_M)
		{
			PlaySoundMem(S_select_M, DX_PLAYTYPE_BACK);
			tmp_M = before_M;
		}
	}
}

// 描画
void Menu_Draw()
{

	// 図形
	if (F_frame1_M == true) { DrawGraph(27, 147, G_select_M, TRUE); }
	if (F_frame2_M == true) { DrawGraph(367, 147, G_select_M, TRUE); }

	// 画像
	DrawGraph(0, 0, G_Main_M, TRUE);
	DrawGraph(30, 150, G_thum_M[0], TRUE);
	DrawGraph(370, 150, G_thum_M[1], TRUE);
}

inline int Appeal()
{
	int flag;
	flag = MessageBox
	(
		NULL,
		TEXT("こちらのゲームモードは来年の文化祭に公開予定です！\n来年も是非来てくださいね！"),
		TEXT("Information"),
		MB_OK | MB_ICONINFORMATION
	);

	if (flag == IDOK)
	{
		SceneMgr_ChangeScene(Scene_Menu);
		return 1;
	}

	return 0;
}