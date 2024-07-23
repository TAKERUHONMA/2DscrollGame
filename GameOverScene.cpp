#include "GameOverScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"

GameOverScene::GameOverScene(GameObject* parent)
{
	over = LoadGraph("Assets/GameOver.png");
	counter = 0;
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE))
	{
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}

	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
}

void GameOverScene::Draw()
{
	DrawGraph(0, 0, over, TRUE);
}

void GameOverScene::Release()
{
}
