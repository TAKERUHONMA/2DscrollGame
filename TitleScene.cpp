#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Player.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
}

void TitleScene::Initialize()
{
}

void TitleScene::Update()
{
	//Player* pPlayer = GetParent()->FindGameObject<Player>();
	if (CheckHitKey(KEY_INPUT_R))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
		//pPlayer->Player();
		//CheckHitKey
	}
}

void TitleScene::Draw()
{
}

void TitleScene::Release()
{
}
