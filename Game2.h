#pragma once
#include <vector>

// 初期化（一回のみ）
void Game2_Init1();

// 初期化（毎回）
void Game2_Init2();

// 更新
void Game2_Update();

// 描画
void Game2_Draw();

// 座標被りチェック
bool Check_Overlap(std::vector<int>::iterator begin, std::vector<int>::iterator end, int num);