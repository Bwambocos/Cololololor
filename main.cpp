#include "DxLib.h"
#include "Keyboard.h"
#include "resource.h"
#include "SceneMgr.h"
#include "Menu.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	// 諸処理
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("Cololololor! v2.0");
	SetGraphMode(640, 480, 32);
	SetWindowSize(640, 480);
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	ChangeWindowMode(TRUE);
	SetWindowIconID(IDI_ICON1);
	DxLib_Init();
	ChangeFont("Meiryo UI");
	SetFontSize(32);
	Menu_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();
		Keyboard_Update();
		SceneMgr_Update();
		SceneMgr_Draw();
		ScreenFlip();
	}

	// 終了処理
	DxLib_End();
	return 0;
}