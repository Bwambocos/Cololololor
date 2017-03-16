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

// �X�V
void SceneMgr_Update();

// �`��
void SceneMgr_Draw();

// �V�[���ύX
void SceneMgr_ChangeScene(Scene_S Nextscene);

Scene_S get_prevScene();