#include "GameOverScene.h"

GameOverScene::GameOverScene(GameObject* parent)
{
	clear = LoadGraph("Assets/GameClear.png");
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, clear, TRUE);
}

void GameOverScene::Release()
{
}
