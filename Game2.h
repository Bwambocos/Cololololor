#pragma once
#include <vector>

// �������i���̂݁j
void Game2_Init1();

// �������i����j
void Game2_Init2();

// �X�V
void Game2_Update();

// �`��
void Game2_Draw();

// ���W���`�F�b�N
bool Check_Overlap(std::vector<int>::iterator begin, std::vector<int>::iterator end, int num);