#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// プレイヤーキャラ
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーの座標をセット
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPosition(int x, int y);
	//void GetPosition(int x, int y) { transform_.position_.x = x, transform_.position_.y = y; }
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	float jumpSpeed;
	bool onGround;
	int counter;
	int animType; //タイプ
	int animFrame; //コマ
	int frameCounter;

	//float cameraX; //カメラの位置
};