#include "DxLib.h"
#include "SceneMgr.h"
#include "Sb.h"
#include "Mouse.h"
#include "Game1.h"
#include "Game2.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

typedef struct
{
	char name[23];
	int score;
}save_data_t;

// ÉOÉçÅ[ÉoÉãä÷êî
int G_Main_Sb = -1;
int G_select_Sb;
int S_select_Sb;
Scene_S Game_Mode;
bool name_change_flag = false;
int Fonthandle_Sb;
char name_Sb[23] = { '\0' };
FILE *fp;
save_data_t save_data[12];
bool save_flag = false;
bool F_frame1_Sb = false;
bool F_sound1_Sb = false;
int before_Sb = -1;
int tmp_Sb = -1;
int Score_Sb;
int Level_Sb;
char Filename_Sb[50] = { '\0' };

// èâä˙âª
void Sb_Init()
{
	Game_Mode = get_prevScene();
	if (G_Main_Sb == -1)
	{
		G_Main_Sb = LoadGraph("data\\graph\\Sb_Main.png");
		G_select_Sb = LoadGraph("data\\graph\\Result_select.png");
		S_select_Sb = LoadSoundMem("data\\sound\\select.wav");
		Fonthandle_Sb = CreateFontToHandle("Meiryo UI", 18, 5, DX_FONTTYPE_ANTIALIASING_8X8);
	}
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 23; j++) { save_data[i].name[j] = '\0'; }
		save_data[i].score = 0;
	}
	if (Game_Mode == Scene_Game1)
	{
		Score_Sb = getScore_G1();
		Level_Sb = getLevel_G1();
		sprintfDx(Filename_Sb, "data\\save\\t1\\dog_food_%d.dat", Level_Sb);
	}
	if (Game_Mode == Scene_Game2)
	{
		Score_Sb = getScore_G2();
		Level_Sb = getLevel_G2();
		sprintfDx(Filename_Sb, "data\\save\\t2\\dog_food_%d.dat", Level_Sb);
	}
	if (errno_t error = (fopen_s(&fp, Filename_Sb, "rb")) != 0 || fp == NULL)
	{
		printfDx("FILE READ ERROR\n");
	}

	else
	{
		for (int i = 0; i < 12; i++)
		{
			fread(&save_data[i], sizeof(save_data_t), 1, fp);
		}
		fclose(fp);
	}
	if (Score_Sb > save_data[11].score) { save_flag = true; }
	name_change_flag = false;
}

// çXêV
void Sb_Update()
{
	if (save_flag == false)
	{
		if (CheckMouseIn(150, 430, 430, 480) == true)
		{
			F_frame1_Sb = true; F_sound1_Sb = true; before_Sb = 1;
		}
		if (CheckMouseIn(150, 430, 430, 480) == false)
		{
			F_frame1_Sb = false; F_sound1_Sb = false; before_Sb = -1;
		}
		if (CheckMouseClick(150, 430, 430, 480) == true) { SceneMgr_ChangeScene(Scene_Menu); }
		if (F_sound1_Sb == true)
		{
			if (before_Sb != tmp_Sb)
			{
				PlaySoundMem(S_select_Sb, DX_PLAYTYPE_BACK);
				tmp_Sb = before_Sb;
			}
		}
	}
	else
	{
		DrawStringToHandle(25, 25, "ÉXÉRÉAÇ™ÉâÉìÉLÉìÉOÇ…åfç⁄Ç≥ÇÍÇ‹Ç∑ÅIñºëOÇì¸óÕÇµÇƒâ∫Ç≥Ç¢", GetColor(222, 0, 0), Fonthandle_Sb);
		KeyInputString(30, 80, 10, name_Sb, TRUE);
		for (int i = 0; i < 12; i++)
		{
			if ((strcmp(save_data[i].name, name_Sb)) == 0)
			{
				switch (Game_Mode)
				{
				case Scene_Game1:
					save_data[i].score = getScore_G1();
					break;
				case Scene_Game2:
					save_data[i].score = getScore_G2();
				}
				name_change_flag = true;
				break;
			}
		}
		if (name_change_flag == false)
		{
			strcpy_s(save_data[11].name, name_Sb);
			switch (Game_Mode)
			{
			case Scene_Game1:
				save_data[11].score = getScore_G1();
				break;
			case Scene_Game2:
				save_data[11].score = getScore_G2();
				break;
			}
		}
		sort(begin(save_data), end(save_data), [](const save_data_t&l, const save_data_t&r) {return l.score > r.score; });
		switch (Game_Mode)
		{
		case Scene_Game1:
			Level_Sb = getLevel_G1();
			sprintfDx(Filename_Sb, "data\\save\\t1\\dog_food_%d.dat", Level_Sb);
			break;
		case Scene_Game2:
			Level_Sb = getLevel_G2();
			sprintfDx(Filename_Sb, "data\\save\\t2\\dog_food_%d.dat", Level_Sb);
			break;
		}
		if (errno_t error = (fopen_s(&fp, Filename_Sb, "wb")) != 0 || fp == NULL)
		{
			printfDx("FILE WRITE ERROR\n");
		}
		else
		{
			for (int i = 0; i < 11; i++)
			{
				fwrite(&save_data[i], sizeof(save_data_t), 1, fp);
			}
			fclose(fp);
		}
		save_flag = false;
	}
}

// ï`âÊ
void Sb_Draw()
{
	if (save_flag == false)
	{
		DrawGraph(0, 0, G_Main_Sb, TRUE);
		const char*const num[] = { "ÇP", "ÇQ", "ÇR", "ÇS", "ÇT", "ÇU", "ÇV", "ÇW", "ÇX", "10", "11", "12" };
		for (int i = 0; i < 6; i++)
		{
			if ((strcmp(save_data[i].name, name_Sb)) == 0) { DrawFormatStringToHandle(25, 80 + 50 * i, GetColor(222, 0, 0), Fonthandle_Sb, "Åy%sà Åz%s %dì_", num[i], save_data[i].name, save_data[i].score); }
			else { DrawFormatStringToHandle(25, 80 + 50 * i, GetColor(255, 255, 255), Fonthandle_Sb, "Åy%sà Åz%s %dì_", num[i], save_data[i].name, save_data[i].score); }
		}
		for (int i = 0; i < 6; i++)
		{
			if ((strcmp(save_data[i + 6].name, name_Sb)) == 0) { DrawFormatStringToHandle(320, 80 + 50 * i, GetColor(222, 0, 0), Fonthandle_Sb, "Åy%sà Åz%s %dì_", num[i + 6], save_data[i + 6].name, save_data[i + 6].score); }
			else { DrawFormatStringToHandle(320, 80 + 50 * i, GetColor(255, 255, 255), Fonthandle_Sb, "Åy%sà Åz%s %dì_", num[i + 6], save_data[i + 6].name, save_data[i + 6].score); }
		}
		if (F_frame1_Sb == true) { DrawExtendGraph(150, 430, 430, 480, G_select_Sb, TRUE); }
	}
}