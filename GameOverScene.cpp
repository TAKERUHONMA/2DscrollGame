#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"

GameOverScene::GameOverScene(GameObject* parent)
{
	clear = LoadGraph("Assets/GameClear.png");
	counter = 0;
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T))
	{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, clear, TRUE);
}

void GameOverScene::Release()
{
}
