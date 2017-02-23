#include "DxLib.h"
#include "SceneMgr.h"
#include "Menu.h"
#include "Game1.h"
#include "Game2.h"
#include "Result.h"
#include "Sb.h"

// グローバル変数
static Scene_S Scene = Scene_Menu;
bool game1_flag1 = true, game1_flag2 = true, game2_flag1 = true, game2_flag2 = true, result_flag = true, sb_flag = true;


// 更新
void SceneMgr_Update()
{
	switch (Scene)
	{
	case Scene_Menu:
		Menu_Update();
		break;

	case Scene_Game1:
		Game1_Update();
		break;

	case Scene_Game2:
		Game2_Update();
		break;

	case Scene_Result:
		Result_Update();
		break;

	case Scene_Sb:
		Sb_Update();
		break;
	}
}

// 描画
void SceneMgr_Draw()
{
	switch (Scene)
	{
	case Scene_Menu:
		Menu_Draw();
		break;

	case Scene_Game1:
		Game1_Draw();
		break;

	case Scene_Game2:
		Game2_Draw();
		break;

	case Scene_Result:
		Result_Draw();
		break;

	case Scene_Sb:
		Sb_Draw();
		break;
	}
}

// シーン変更
void SceneMgr_ChangeScene(Scene_S Nextscene)
{
	Scene = Nextscene;
	switch (Scene)
	{
	case Scene_Game1:
		if (game1_flag1 == true)
		{
			Game1_Init1(); game1_flag1 = false;
		}
		Game1_Init2();
		break;

	case Scene_Game2:
		if (game2_flag1 == true)
		{
			Game2_Init1(); game2_flag1 = false;
		}
		Game2_Init2();
		break;

	case Scene_Result:
		if (result_flag == true)
		{
			Result_Init(); result_flag = false;
		}
		break;

	case Scene_Sb:
		Sb_Init();
		break;
	}
}