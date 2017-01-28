#pragma once

// 初期化（一回のみ）
void Game1_Init1();

// 初期化（毎回）
void Game1_Init2();

// 更新
void Game1_Update();

// 描画
void Game1_Draw();

// ClearかOverか返す
int getCorO_G1();

// Scoreを返す
int getScore_G1();

// Levelを返す
int getLevel_G1();