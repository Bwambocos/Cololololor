#pragma once
#include "DxLib.h"

typedef enum
{
	Scene_Menu,
	Scene_Game1,
	Scene_Game2,
	Scene_Result,
	Scene_Sb,
}Scene_S;

// 更新
void SceneMgr_Update();

// 描画
void SceneMgr_Draw();

// シーン変更
void SceneMgr_ChangeScene(Scene_S Nextscene);

Scene_S get_prevScene();