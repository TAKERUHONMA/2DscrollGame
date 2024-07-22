#include "GameClear.h"
#include "Engine/SceneManager.h"

GameClear::GameClear(GameObject* parent)
{
	clear = LoadGraph("Assets/GameClear.png");
}

void GameClear::Initialize()
{
}

void GameClear::Update()
{
	if (CheckHitKey(KEY_INPUT_R))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameClear::Draw()
{
	DrawGraph(0, 0, clear, TRUE);
}

void GameClear::Release()
{
}
