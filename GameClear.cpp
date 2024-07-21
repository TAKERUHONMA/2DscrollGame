#include "GameClear.h"

GameClear::GameClear(GameObject* parent)
{
	clear = LoadGraph("Assets/GameClear.png");
}

void GameClear::Initialize()
{
}

void GameClear::Update()
{
}

void GameClear::Draw()
{
	DrawGraph(0, 0, clear, TRUE);
}

void GameClear::Release()
{
}
