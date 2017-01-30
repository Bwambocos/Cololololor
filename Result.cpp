#include "Result.h"
#include "SceneMgr.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Game1.h"
#include "Mouse.h"

// グローバル変数
int G_Main_R[2];
int G_Select_R;
int S_Select_R;
int CorO_flag_R;
bool F_frame_R = false;
bool F_frame1_R = false;
bool F_frame2_R = false;
bool F_sound_R = false;
bool F_sound1_R = false;
bool F_sound2_R = false;
int before_R = -1;
int tmp_R = -1;

// 初期化
void Result_Init()
{
	G_Main_R[0] = LoadGraph("data\\graph\\Clear_Main.png");
	G_Main_R[1] = LoadGraph("data\\graph\\Over_Main.png");
	G_Select_R = LoadGraph("data\\graph\\Result_select.png");
	S_Select_R = LoadSoundMem("data\\sound\\select.wav");
}

// 更新
void Result_Update() {
	if (getCorO_G1() == 0) { CorO_flag_R = 0; }
	if (getCorO_G1() == -1) { CorO_flag_R = -1; }

	if (CorO_flag_R == 0)
	{
		if (CheckMouseIn(100, 150, 530, 200) == true)
		{
			F_frame_R = true; F_sound_R = true; before_R = 0;
		}
		if (CheckMouseIn(100, 150, 530, 200) == false)
		{
			F_frame_R = false; F_sound_R = false; before_R = -1;
		}
		if (CheckMouseClick(100, 150, 530, 200) == true) { SceneMgr_ChangeScene(Scene_Sb); }
		if (CheckMouseIn(70, 250, 560, 320) == true)
		{
			F_frame1_R = true; F_sound1_R = true; before_R = 1;
		}
		if (CheckMouseIn(70, 250, 560, 320) == false)
		{
			F_frame1_R = false; F_sound1_R = false; before_R = -1;
		}
		if (CheckMouseClick(70, 250, 560, 320) == true) { SceneMgr_ChangeScene(Scene_Game1); }
	}
	if (CorO_flag_R == -1)
	{
		if (CheckMouseIn(70, 240, 560, 290) == true)
		{
			F_frame1_R = true; F_sound1_R = true; before_R = 1;
		}
		if (CheckMouseIn(70, 240, 560, 290) == false)
		{
			F_frame1_R = false; F_sound1_R = false; before_R = -1;
		}
		if (CheckMouseClick(70, 240, 560, 290) == true) { SceneMgr_ChangeScene(Scene_Game1); }
	}
	if (CheckMouseIn(70, 350, 560, 420) == true)
	{
		F_frame2_R = true; F_sound2_R = true; before_R = 2;
	}
	if (CheckMouseIn(70, 350, 560, 420) == false)
	{
		F_frame2_R = false; F_sound2_R = false; before_R = -1;
	}
	if (CheckMouseClick(70, 350, 560, 420) == true) { SceneMgr_ChangeScene(Scene_Menu); }
	if (F_sound1_R == true || F_sound2_R == true)
	{
		if (before_R != tmp_R)
		{
			PlaySoundMem(S_Select_R, DX_PLAYTYPE_BACK);
			tmp_R = before_R;
		}
	}
}

// 描画
void Result_Draw()
{
	if (CorO_flag_R == -1)
	{ 
		DrawGraph(0, 0, G_Main_R[1], TRUE);
	}
	if (CorO_flag_R == 0)
	{
		DrawGraph(0, 0, G_Main_R[0], TRUE);
	}

	if (CorO_flag_R == 0)
	{
		if (F_frame_R == true)
		{
			DrawGraph(60, 145, G_Select_R, TRUE);
		}
		if (F_frame1_R == true) { DrawGraph(60, 245, G_Select_R, TRUE); }
	}
	if (CorO_flag_R == -1)
	{
		if (F_frame1_R == true) { DrawGraph(60, 225, G_Select_R, TRUE); }
	}
	if (F_frame2_R == true){ DrawGraph(60, 355, G_Select_R, TRUE); }
}